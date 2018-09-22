{
    'target_defaults': {
        'defines': [
            '_WIN32_WINNT=0x0600',
        ],
        'msbuild_settings': {
            'ClCompile': {
                'WarningLevel': 'Level3',
                'Optimization': 'Full',
                'FunctionLevelLinking': 'true',
            },
            'Lib': {
                'LinkTimeCodeGeneration': 'true',
            },
        },
        'msvs_settings': {
            'VCCLCompilerTool': {
                'WarningLevel': '3',
                'Optimization': '3',
                'EnableFunctionLevelLinking': 'true',
            },
            'VCLibrarianTool': {
                'LinkTimeCodeGeneration': 'true',
            },
        },
    },
    'targets': [
        {
            'target_name': 'addon',
            'include_dirs': [
                '<!(node -e "require(\'nan\')")',
            ],
            'sources': [
                'addon.cpp',
                'system_icon.cpp',
            ],
            'link_settings': {
                'libraries': [
                    'Gdiplus.lib',
                ],
            },
        },
    ],
}
