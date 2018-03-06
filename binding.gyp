{
	'targets': [
	{
		'target_name': 'napi_openal',
		'sources': [
			'src/napi_openal.c',
		],
		'conditions': [[
			'OS=="mac"', {
				'libraries': [
					'/usr/local/opt/openal-soft/lib/libopenal.dylib',
				],
				'xcode_settings': {
            		'OTHER_LDFLAGS': [
              			'-undefined dynamic_lookup',
              			'-framework Cocoa',
              			'-framework OpenGL',              			
              			'-framework OpenAL',
            		]
          		},
				'include_dirs': [
					'/usr/local/include',
					'/usr/local/opt/openal-soft/include/AL'
				]
			}
		]],
		'defines': [
			'_THREAD_SAFE',
			'ENABLE_ARG_CHECKING',
		]
	}
	]
}
