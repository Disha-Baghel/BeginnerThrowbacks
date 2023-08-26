#include <iostream>
#include "Play.h"

static Uint8 *audio_pos;
static Uint32 audio_len;

void my_audio_callback(void *userdata, Uint8 *stream, int len) {

	if (audio_len ==0)
		return;

	len = ( len > audio_len ? audio_len : len );
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);

	audio_pos += len;
	audio_len -= len;
}


void play(const char* MUS_PATH)
{
    static Uint32 wav_length;
	static Uint8 *wav_buffer;
	static SDL_AudioSpec wav_spec;


	SDL_LoadWAV(MUS_PATH, &wav_spec, &wav_buffer, &wav_length);

	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;

	audio_pos = wav_buffer;
	audio_len = wav_length;

	if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
	  std::cout<<"Couldn't open audio: "<<SDL_GetError();
	  exit(-1);
	}

	SDL_PauseAudio(0);

	while ( audio_len > 0 ) {
		SDL_Delay(100);
	}

	SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);
}
