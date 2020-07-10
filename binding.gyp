{
    "target_defaults": {
        "defines": [
            "_WIN32_WINNT=0x0600",
        ],
        "msbuild_settings": {
            "ClCompile": {
                "WarningLevel": "Level3",
                "Optimization": "Full",
                "FunctionLevelLinking": "true",
            },
            "Lib": {
                "LinkTimeCodeGeneration": "true",
            },
        },
        "msvs_settings": {
            "VCCLCompilerTool": {
                "WarningLevel": "3",
                "Optimization": "3",
                "EnableFunctionLevelLinking": "true",
            },
            "VCLibrarianTool": {
                "LinkTimeCodeGeneration": "true",
            },
        },
    },
    "targets": [
        {
            "target_name": "shellImageWin",
            "cflags!": [ "-fno-exceptions" ],
            "cflags_cc!": [ "-fno-exceptions" ],
            "sources": ["addon.cpp"],
            "link_settings": {
                "libraries": ["Gdiplus.lib"],
            },
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
        }
    ]
}
