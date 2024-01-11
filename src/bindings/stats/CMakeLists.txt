target_sources(_numoop PRIVATE
        load_bindings.cpp
        load_bindings.hpp
        stats_bindings.cpp
        stats_bindings.hpp
)
add_subdirectory(dataframe_bindings)
