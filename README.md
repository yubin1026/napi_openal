# napi_openal

The goal of this library provides OpenAL bindings for node using N-API.


## Supported OS
Currently only macOS


## Installation

```javascript
brew install SDL2 shivavg openal-soft freealut

brew install ffmpeg --enable-libass --with-fdk-aac --with-ffplay --with-freetype 
 --with-frei0r --with-libass --with-libvo-aacenc --with-libvorbis --with-libvpx 
 --with-opencore-amr --with-openjpeg --with-opus --with-rtmpdump --with-schroedinger 
 --with-speex --with-theora --with-tools --with-sdl2
```

```javascript
npm install napi_openal
```

## Usage

Open media file using ffmpeg
```javascript
AV.av_register_all();
ic = AV.avformat_open_input(path);
AV.av_dump_format(ic, path)
AV.avformat_find_stream_info(ic);

audioStream = AV.av_find_best_stream(ic, AV.AVMEDIA_TYPE_AUDIO);

audioCtx = AV.avformat_context(ic, audioStream);
AV.avcodec_open(audioCtx);
```
Open audio device using Open AL
```javascript
// open al handling...
aDevice = AL.alcOpenDevice();
aContext = AL.alcCreateContext(aDevice);

// make active context
AL.alcMakeContextCurrent(aContext);
alSource = AL.alGenSources(1);
AL.alGenBuffers();
AL.alSourcei(alSource, AL.AL_LOOPING, AL.AL_FALSE);
AV.avcodec_resampler(audioCtx);
```

Play audio stream
```javascript
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

```

