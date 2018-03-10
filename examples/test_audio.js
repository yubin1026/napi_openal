'use strict';

const util = require("util");
const fs = require('fs');

const SDL2 = require('napi_sdl2');
const VG = require('napi_openvg');
const AL = require('napi_openal');
const AV = require('napi_ffmpeg');

let context = {
	window : null
}
let reflow_flag = true;

// ffmpeg
let ic;
let audioStream = -1;
let audioCtx;

// AL
let aDevice;
let aContext;
let alSource;

let a_count = 0;
function play_audio(context) {
	let ret = AV.avcodec_decode(ic, null, -1, audioCtx, audioStream);
	if(ret.type != 1) return;

	// Prefill all of the buffers
    let sample_rate = AV.avcodec_sample_rate(audioCtx);
    if(a_count < 3) {
        AL.alBufferData(a_count, AL.AL_FORMAT_STEREO16, ret.buffer, sample_rate);
        a_count++;
        ret = ret.buffer = null;
        
        if(a_count == 3) {
            AL.alSourceQueueBuffersAll(alSource);
            AL.alSourcePlay(alSource);
        }
    } else {
    	let val = 0;
            /* Check if OpenAL is done with any of the queued buffers */
        do {
            val = AL.alGetSourcei(alSource, AL.AL_BUFFERS_PROCESSED);
            AV.av_usleep(10);
        } while(val <= 0);
        
        /* Pop the oldest queued buffer from the source, fill it
         * with the new data, then requeue it */
        //let buffer;
        while(val--) {
        	AL.alFillData(alSource, ret.buffer, sample_rate);
        }
        ret = ret.buffer = null;
        
        /* Make sure the source is still playing, and restart it if needed. */
        val = AL.alGetSourcei(alSource, AL.AL_SOURCE_STATE);
        if(val != AL.AL_PLAYING)
            AL.alSourcePlay(alSource);
    }
}

function main()
{
	SDL2.SDL_Init(SDL2.SDL_INIT_EVERYTHING);
	SDL2.SDL_GL_SetAttribute (SDL2.SDL_GL_CONTEXT_FLAGS, SDL2.SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL2.SDL_GL_SetAttribute(SDL2.SDL_GL_DOUBLEBUFFER, 1);
	SDL2.SDL_GL_SetAttribute(SDL2.SDL_GL_MULTISAMPLEBUFFERS, 8);
	SDL2.SDL_GL_SetAttribute(SDL2.SDL_GL_MULTISAMPLESAMPLES, 8);
	SDL2.SDL_GL_SetAttribute(SDL2.SDL_GL_DEPTH_SIZE, 24);
	SDL2.SDL_GL_SetAttribute(SDL2.SDL_GL_STENCIL_SIZE, 8);
	SDL2.SDL_GL_SetAttribute( SDL2.SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
	SDL2.SDL_GL_SetAttribute( SDL2.SDL_GL_CONTEXT_MINOR_VERSION, 1 );

	let [screen_width, screen_height] = [800, 100];

	let sdl_window = SDL2.SDL_CreateWindow("Audio Player", 
		0, 0, screen_width, screen_height, SDL2.SDL_WINDOW_OPENGL | SDL2.SDL_WINDOW_SHOWN | SDL2.SDL_WINDOW_RESIZABLE);
	let sdl_context = SDL2.SDL_GL_CreateContext( sdl_window );
	SDL2.SDL_GL_SetSwapInterval( 1 );
	 
	let quit = false;
	VG.vgCreateContextSH(screen_width, screen_height);
	
	context.window = sdl_window;

	//let path = "/Users/kyeongwoon/Desktop/movie/미드/Suits Season 1/Suits.S01E01.720p.HDTV.x264.mkv";
	let path = '/Users/kyeongwoon/Desktop/movie/영어/Learn Real English/Assisted Living Conversation.mp3';
	AV.av_register_all();
	ic = AV.avformat_open_input(path);
	AV.av_dump_format(ic, path)
	AV.avformat_find_stream_info(ic);

	audioStream = AV.av_find_best_stream(ic, AV.AVMEDIA_TYPE_AUDIO);

	audioCtx = AV.avformat_context(ic, audioStream);
	AV.avcodec_open(audioCtx);

	// open al handling...
	aDevice = AL.alcOpenDevice();
	aContext = AL.alcCreateContext(aDevice);
    
    // make active context
    AL.alcMakeContextCurrent(aContext);
    alSource = AL.alGenSources(1);
    AL.alGenBuffers();
    AL.alSourcei(alSource, AL.AL_LOOPING, AL.AL_FALSE);
    AV.avcodec_resampler(audioCtx);

	while(!quit)
	{
		let event = {};
		SDL2.SDL_PumpEvents();
		while(1) {
			let ret = SDL2.SDL_PeepEvents(event, 1, SDL2.SDL_GETEVENT, SDL2.SDL_FIRSTEVENT, SDL2.SDL_LASTEVENT);
			if(ret == 1) break;
			play_audio(context);
			SDL2.SDL_PumpEvents();
		}

		switch(event.type)
		{
			case "MOUSEBUTTONDOWN":
				break;
			case "MOUSEBUTTONUP":
				break;
			case "MOUSEWHEEL":
				break;
			case "WINDOWEVENT":
				if(event.event == "WINDOWEVENT_RESIZED") {
					[screen_width, screen_height] = SDL2.SDL_GetWindowSize(context.window);

					VG.vgResizeSurfaceSH(screen_width, screen_height);

				} else if(event.event == "WINDOWEVENT_SIZE_CHANGED") {
		
				} else if(event.event == "WINDOWEVENT_EXPOSED") {
				}
				break;
			case "KEYDOWN":
				break;
			case "QUIT":
				quit = true;
				break;
		}
	}

	AV.avcodec_close(audioCtx);
    AV.avformat_close_input(ic);
	
	VG.vgDestroyContextSH();
	SDL2.SDL_DestroyWindow(context.window);
	SDL2.SDL_Quit();
}

main();
