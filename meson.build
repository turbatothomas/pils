project(
	'pilsner',
	'cpp',
	default_options : ['cpp_std=c++17', 'buildtype=debugoptimized'],
	version: '0.6.1'
)

compiler = meson.get_compiler('cpp').get_id()

sdl_dep = []
include_dirs = []
link_args = []
compile_args = []

win_sdl_path = join_paths(meson.current_source_dir(),'SDL2-2.0.8')

if compiler == 'gcc'
  sdl_dep = dependency('SDL2')
  sdl_image_dep = dependency('SDL2_image')
  link_args = ['-lstdc++fs']
elif host_machine.system() == 'windows'
  win_sdl2_lib = []
  win_include_dirs = include_directories([join_paths(win_sdl_path, 'include')])
  win_libs_dir_64 = join_paths(win_sdl_path, 'lib', 'x64')
  win_sdl2_lib += meson.get_compiler('cpp').find_library('SDL2', dirs: [win_libs_dir_64])
  win_sdl2_lib += meson.get_compiler('cpp').find_library('SDL2main', dirs: [win_libs_dir_64])

  sdl_image_dep = meson.get_compiler('cpp').find_library('SDL2_image', dirs: [win_libs_dir_64])
  sdl_dep += win_sdl2_lib

  include_dirs += win_include_dirs
  compile_args += '/std:c++latest'
  link_args += '/SUBSYSTEM:CONSOLE'
else
	link_args = []
endif

deps = [sdl_dep, sdl_image_dep]

src = ['src/Birra.cpp', 'src/Game.cpp', 'src/GirlsManager.cpp', 'src/GirlWindow.cpp', 'src/global.cpp', 'src/main.cpp', 'src/MBeer.cpp', 'src/Menu.cpp', 'src/Oggetto.cpp', 'src/PhysicObject.cpp', 'src/Player.cpp', 'src/SubWindow.cpp']

if host_machine.system() == 'windows'
	installdir = join_paths(
		meson.current_source_dir(),
		get_option('win_release_dir')
	)
else
	installdir = join_paths(
		meson.current_source_dir(),
		get_option('linux_release_dir')
	)
endif

executable(
	'pilsner',
	src,
	dependencies: deps,
	cpp_args: compile_args,
	link_args: link_args,
	include_directories: include_dirs,
	install: true,
	install_dir: installdir
)

# TODO Per winzzoooz bisogna copiare anche le dll

install_subdir(
	'res',
	install_dir : installdir
)

install_subdir(
	'girls',
	install_dir : installdir
)

if host_machine.system() == 'windows'
	dll_path = join_paths(win_sdl_path, 'lib/x64/')
	dlls = [
		join_paths(dll_path, 'SDL2.dll'),
		join_paths(dll_path, 'SDL2_image.dll'),
		join_paths(dll_path, 'libjpeg-9.dll'),
		join_paths(dll_path, 'libpng16-16.dll'),
		join_paths(dll_path, 'zlib1.dll')
		#join_paths(dll_path, 'libtiff-5.dll')
	]

	install_data(
		dlls,
		install_dir : installdir
	)
endif
