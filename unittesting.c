/*
 * Copyright (c) 2011, Josep Sanjuas <jsanjuas@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <assert.h>
#include <stdlib.h>
#include <check.h>
#include "unittesting.h"

#define MAX_TESTS 1024
int ntests = 0;

typedef void (*test_t)(int);
test_t tests[MAX_TESTS];
char * testnames[MAX_TESTS];

void
register_test(void (*f)(int), char *name)
{
    assert(ntests < MAX_TESTS);
    tests[ntests] = f;
    testnames[ntests] = name;
    ntests++;
}

int run_test_suite(Suite *s)
{
    int number_failed;

    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed;
}

int
run_tests(void)
{
    Suite *s = suite_create("");
    int number_failed = 0;
    int i;

    for (i = 0; i < ntests; i++) {
        TCase *c = tcase_create(testnames[i]);
        tcase_add_test(c, tests[i]);
        suite_add_tcase(s, c);
    }

    number_failed += run_test_suite(s);
    return number_failed;
}

