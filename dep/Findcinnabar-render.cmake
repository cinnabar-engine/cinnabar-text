find_path(CE_RENDER_INCLUDE_DIR cinnabar-render/cinnabar-render.hpp)
find_library(CE_RENDER_LIBRARY cinnabar-render)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(cinnabar-render
	REQUIRED_VARS
		CE_RENDER_LIBRARY
		CE_RENDER_INCLUDE_DIR
	VERSION_VAR
		CE_RENDER_VERSION
)


set(CE_RENDER_FOUND ${CINNABAR-RENDER_FOUND})

set(CE_RENDER_LIBRARIES ${CE_RENDER_LIBRARY})
set(CE_RENDER_INCLUDE_DIRS ${CE_RENDER_INCLUDE_DIR})

mark_as_advanced(CE_RENDER_LIBRARY CE_RENDER_INCLUDE_DIR)