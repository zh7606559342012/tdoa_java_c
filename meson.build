project('xlmf_tdoa', 'c', 'cpp',
    version : '1.0.0',
    license : 'AGPL-3.0-or-later',
    meson_version : '>= 0.43.0',
)

install_root = get_option('prefix')
header_install_root = install_root / 'include'

tdoa_headers = files('''
    javatoc.h
    tdoa.h
'''.split())

tdoa_sources = files('''
    javatoc.h
    tdoa.cpp
'''.split())

libtdoa_chan = dependency('tdoa_chan', required : true)

#static_library('xlmf_tdoa',
#    sources: tdoa_sources,
#    dependencies : [libitpp_dep],
#    install : true)

shared_library('xlmf_tdoa',
    sources: tdoa_sources,
    dependencies: [libtdoa_chan],
    install : true)

install_headers(tdoa_headers,
    install_dir: header_install_root
)
