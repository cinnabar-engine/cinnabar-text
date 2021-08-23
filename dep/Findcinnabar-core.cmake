find_path(CE_CORE_INCLUDE_DIR cinnabar-core/time.hpp)
find_library(CE_CORE_LIBRARY cinnabar-core)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(cinnabar-core
	REQUIRED_VARS
		CE_CORE_LIBRARY
		CE_CORE_INCLUDE_DIR
	VERSION_VAR
		CE_CORE_VERSION
)


set(CE_CORE_FOUND ${CINNABAR-CORE_FOUND})

set(CE_CORE_LIBRARIES ${CE_CORE_LIBRARY})
set(CE_CORE_INCLUDE_DIRS ${CE_CORE_INCLUDE_DIR})

mark_as_advanced(CE_CORE_LIBRARY CE_CORE_INCLUDE_DIR)