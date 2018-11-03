project('Behind Computer', 'cpp')
WT_ROOT = get_option('wtroot')
c = meson.get_compiler('cpp')
src = meson.source_root()
dirs = [src + '/lib/x86', WT_ROOT + '/lib', WT_ROOT + '/lib/x86_64-linux-gnu', WT_ROOT + '/lib/i386-linux-gnu']
incs = include_directories(WT_ROOT + '/include')

wtlibs = ['wt', 'wtdbo', 'wthttp', 'wtdbomysql']
wtdeps = []

foreach l : wtlibs
  wtdeps += c.find_library(l, dirs : dirs)
endforeach

wt = declare_dependency(dependencies : wtdeps, include_directories : incs)
boost = dependency('boost', modules : ['system', 'filesystem', 'regex'])
thread_dep = dependency('threads')
deps = [wt, boost, thread_dep]
src = [
  'src/main.cpp',
  'src/AddCitizen.cpp',
  'src/MainPage.cpp',
  'src/MyApp.cpp',
  'src/PersonalPage.cpp',
  'src/Post.cpp',
  'src/TweetsContainer.cpp',
  'src/TweetWidget.cpp',
  'src/domain/Tweet.cpp',
  'src/domain/Citizen.cpp',
]

executable('bc', src, 
	build_rpath : '$ORIGIN/lib',
	dependencies : deps
)