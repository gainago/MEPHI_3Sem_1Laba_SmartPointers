#include "Tests.h"
#include "Tests/Tests_unique_ptr.h"
#include "Tests/Tests_shared_ptr.h"
#include "Tests/Tests_weak_ptr.h"

void Tests_unique_ptr()
{
    Test_unique_release();

    Test_unique_reset();

    Test_unique_swap();

    Test_unique_get();

    Test_unique_operator_dereference();

    Test_unique_operator_dereference2();
}

void Tests_shared_ptr()
{
    Test_shared_reset();

    Test_shared_swap();

    Test_shared_get();

    Test_shared_use_count();

    Test_shared_operator_equality();

    Test_shared_operator_dereference();

    Test_shared_operator_dereference2();
}

void Tests_weak_ptr()
{
    Test_weak_reset();

    Test_weak_swap();

    Test_weak_use_count();

    Test_weak_expired();

    Test_weak_lock();
}