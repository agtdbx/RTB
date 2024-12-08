project('RTB', 'cpp',
  version : '1.1',
  default_options : ['warning_level=1', 'cpp_std=c++14'])



conf_data = configuration_data()
conf_data.set('DATA_PATH', get_option('prefix') + '/data')


executable('RTB',
          'src/main.cpp',
          'src/Background.cpp',
          'src/Button.cpp',
          'src/Camera.cpp',
          'src/Functions.cpp',
          'src/Game.cpp',
          'src/Map.cpp',
          'src/Menu.cpp',
          'src/Personnage.cpp',
          'src/Select.cpp',
          'src/Switch.cpp',
          'src/Tuile.cpp',
          'src/Zone.cpp',
       build_rpath: '.',
           dependencies : [
              dependency('sdl2'),
              dependency('sdl2_image', static: true),
              dependency('sdl2_ttf', static: true),
              dependency('sdl2_mixer', static: true),
              dependency('jsoncpp', static: true),
              ],
			include_directories: include_directories('include'),
           install : true)

install_subdir('data', install_dir:'.')
