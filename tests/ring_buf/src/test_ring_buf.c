/*
 * Ring Buffer Module - Homework Test Skeleton
 *
 * test_fresh_state is provided as a worked example. Fill in the remaining
 * 7 ZTEST bodies according to TEST_SPEC.md. Stubs call ztest_test_skip()
 * so the binary builds and runs cleanly before each test is implemented.
 *
 * Run:
 *   west twister -T tests/ring_buf -p native_sim
 */

#include <zephyr/ztest.h>
#include <errno.h>

#include "ring_buf.h"

/*
 * Shared before hook: every suite reinitialises the ring buffer with a
 * capacity of 4 so tests start from a clean, known state. Capacity 4 is
 * enough to exercise FIFO order (push 1, 2, 3) and overflow (full at 4).
 */
static void before(void *f)
{
	ARG_UNUSED(f);
	rb_init(4);
}

/*
 * ============================================================================
 * Test Suite: ring_buf_init
 *
 * Initial state and re-initialization behaviour.
 * ============================================================================
 */
ZTEST_SUITE(ring_buf_init, NULL, NULL, before, NULL, NULL);

/* PROVIDED — study this test before writing the rest. */
ZTEST(ring_buf_init, test_fresh_state)
{
	zassert_true(rb_is_empty(), "Fresh buffer must be empty");
	zassert_equal(rb_count(), 0, "Fresh buffer count must be 0");
	// ztest_test_skip();
}


ZTEST(ring_buf_init, test_reinit_clears_state)
{
	/* (l8-task1): Push a value, call rb_init(4) again, then
	 * verify the buffer is empty and count is 0.
	 * See TEST_SPEC.md "Suite ring_buf_init" #2.
	 */
	rb_push(99);
	rb_init(4);
	zassert_true(rb_is_empty(), "Fresh buffer must be empty #0");
	zassert_equal(rb_count(), 0, "Fresh buffer count must be 0 #0");
	// ztest_test_skip();
}

/*
 * ============================================================================
 * Test Suite: ring_buf_push_pop
 *
 * Single push/pop round-trip, FIFO order, full error path.
 * ============================================================================
 */
ZTEST_SUITE(ring_buf_push_pop, NULL, NULL, before, NULL, NULL);

ZTEST(ring_buf_push_pop, test_single_push_pop)
{
	/* (l8-task1): rb_push(42), rb_pop(&v) -> v == 42, buffer empty after.
	 * See TEST_SPEC.md "Suite ring_buf_push_pop" #1.
	 */
	int v;
	zassert_equal(rb_push(42),0,"Must push value 42 #1");
	zassert_equal(rb_pop(&v),0,"Must pop the value 42 #1");
	zassert_equal(v , 42, "Pop Value must be 42 #1");
	zassert_true(rb_is_empty(), "After one push and one pop  buffer must be empty #1");
	// ztest_test_skip();
}

ZTEST(ring_buf_push_pop, test_fifo_order)
{
	/* (l8-task1): rb_push(1), rb_push(2), rb_push(3); pop three times
	 * and verify the values come out as 1, 2, 3 in that order.
	 * See TEST_SPEC.md "Suite ring_buf_push_pop" #2.
	 */
	int v;
	zassert_equal(rb_push(1),0,"Push value must be 1 in #2");
	zassert_equal(rb_push(2),0,"Push value must be 2 in #2");
	zassert_equal(rb_push(3),0,"Push value must be 3 in #2");
	rb_pop(&v);
	zassert_equal(v,1, "Pop Value must be 1");
	rb_pop(&v);
	zassert_equal(v,2, "Pop Value must be 2");
	rb_pop(&v);
	zassert_equal(v ,3, "Pop Value must be 3");
	zassert_equal(rb_count(), 0, "Buffer count must be 0");
	// ztest_test_skip();
}

ZTEST(ring_buf_push_pop, test_push_full_returns_enospc)
{
	/* (l8-task1): Fill the buffer to its capacity of 4, then push
	 * one more value -> -ENOSPC.
	 * See TEST_SPEC.md "Suite ring_buf_push_pop" #3.
	 */
	zassert_equal(rb_push(1),0,"Must push the value 1 in #3");
	zassert_equal(rb_push(2),0,"Must push the value 2 in #3");
	zassert_equal(rb_push(3),0,"Must push the value 3 in #3");
	zassert_equal(rb_push(4),0,"Must push the value 4 in #3");
	zassert_true(rb_is_full(),"Rb _full should be true #3");
	zassert_equal(rb_push(99),-ENOSPC,"The buffer should be return -ENOSPC #3");
	zassert_equal(rb_count(),4,"rb_count should be 4 #3");
	// ztest_test_skip();
}

/*
 * ============================================================================
 * Test Suite: ring_buf_boundaries
 *
 * Peek semantics and NULL-pointer boundary conditions.
 * ============================================================================
 */
ZTEST_SUITE(ring_buf_boundaries, NULL, NULL, before, NULL, NULL);

ZTEST(ring_buf_boundaries, test_peek_does_not_consume)
{
	/* (l8-task1): rb_push(7); rb_peek(&v) -> v == 7; rb_peek(&v) again
	 * -> v == 7; rb_count() still == 1.
	 * See TEST_SPEC.md "Suite ring_buf_boundaries" #1.
	 */
	int v;
	zassert_equal(rb_push(7),0,"Must push the value 1 in #4"); 
	zassert_equal(rb_peek(&v),0,"rb_peek must give 0 #4");
	zassert_equal(v,7, "Peek Value must be 7 First time #4");
	zassert_equal(rb_peek(&v),0,"rb_peek must give 0 #4");
	zassert_equal(v,7, "Peek Value must be 7 Second time #4");
	zassert_equal(rb_count(),1,"rb_count should be 1 after peek #4");

	// ztest_test_skip();
}

ZTEST(ring_buf_boundaries, test_pop_null_returns_einval)
{
	/* TODO(l8-task1): rb_pop(NULL) -> -EINVAL.
	 * See TEST_SPEC.md "Suite ring_buf_boundaries" #2.
	 */
	zassert_equal(rb_pop(NULL),-EINVAL,"Must be -EINVAL in empty buffer #5"); 

	// ztest_test_skip();
}

ZTEST(ring_buf_boundaries, test_is_full_after_fill)
{
	/* TODO(l8-task1): push 4 values -> rb_is_full() == true, rb_count() == 4.
	 * See TEST_SPEC.md "Suite ring_buf_boundaries" #3.
	 */
	zassert_equal(rb_push(1),0,"Must push the value 1 in #6");
	zassert_equal(rb_push(2),0,"Must push the value 2 in #6");
	zassert_equal(rb_push(3),0,"Must push the value 3 in #6");
	zassert_equal(rb_push(4),0,"Must push the value 4 in #6");
	zassert_true(rb_is_full(), "Buffer must be full  #6");
	zassert_equal(rb_count(),4," Buffer should have 4 elements  #6");
	
	// ztest_test_skip();
}
