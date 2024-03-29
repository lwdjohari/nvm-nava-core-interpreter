// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

// this include gives us _POSIX_MAPPED_FILES to test and mmap_input<> if it is set
#include <tao/pegtl/file_input.hpp>

#if defined( _POSIX_MAPPED_FILES ) || defined( _WIN32 )

#include "test.hpp"
#include "verify_file.hpp"

namespace TAO_PEGTL_NAMESPACE
{
   void unit_test()
   {
      verify_file< mmap_input<> >();
   }

}  // namespace TAO_PEGTL_NAMESPACE

#include "main.hpp"

#else

int main()
{
   return 0;
}

#endif
