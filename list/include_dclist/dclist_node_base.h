#ifndef __dclist_node_base_h
#define __dclist_node_base_h

#include <stddef.h>
#include <assert.h>

// Double Chain List
// 双向循环链表节点, 不包含数据
typedef struct DCList_node_base *DCList_link;

/**
 * 双向链表节点基类
 *            ___  next      
 *           |   |------>
 *     <-----|___|       
 *       prev
 */
struct DCList_node_base {
	DCList_link next;
	DCList_link prev;
};

/**
 * 初始化NIL结点
 *         ____
 *        |    |
 *        V    |
 *   .--[nil]--'
 *   |    A    
 *   |____|     
 */
inline 
void list_nil_init(DCList_link nil)
{
	// 初始化nil节点
	nil->prev = nil->next = nil;
}


/**
 * 在链表的x节点前插入t节点
 *            ___                ___
 *           |   |------------->|   |------>
 *    <------|___|<-------------|___|
 *                                ^-x
 *                  ___        
 *                 |   |------>
 *            <----|___|       
 *                   ^-t       
 * =========================================
 *            ___                ___
 *           |   |------------->|   |------>
 *    <------|___|<-------------|___|
 *             A                 A ^-x
 *             |(1) ___          |(2)
 *             |   |   |---------'
 *             '---|___|       
 *                   ^-t       
 * =========================================
 *            ___                ___
 *           |   |--.     .---->|   |------>
 *    <------|___|  |(3)  |  .--|___|
 *             A    |  (4)|  |    ^-x
 *             |    V__   |  |
 *             |   |   |--'  |
 *             '---|___|<----'
 *                   ^-t
 */
inline
void list_insert(DCList_link x, DCList_link y)
{
    assert(x != NULL && t != NULL);
	t->prev = x->prev;      // (1)
	t->next = x;            // (2)
	t->prev->next = t;      // (3)
	t->next->prev = t;      // (4)
}

/**
 * 在链表的x节点前插入[a,b]节点
 *            ___                           ___
 *           |   |------------------------>|   |------>
 *    <------|___|<------------------------|___|
 *                                           ^-x
 *                  ___         ___        
 *                 |   |------>|   |------>
 *            <----|___|<------|___|       
 *                   ^-a         ^-b
 * =====================================================
 *            ___                           ___
 *           |   |------------------------>|   |------>
 *    <------|___|<------------------------|___|
 *             A                            A ^-x
 *             |(1) ___         ___         |(2)
 *             |   |   |------>|   |--------'
 *             '---|___|<------|___|      
 *                   ^-a         ^-b      
 * =====================================================
 *            ___                            ___
 *           |   |--.                 .---->|   |------>
 *    <------|___|  |(3)              |  .--|___|
 *             A    |              (4)|  |    ^-x
 *             |    V__         ___   |  |
 *             |   |   |------>|   |--'  |
 *             '---|___|<------|___|<----'
 *                   ^-a         ^-b
 */
inline
void list_insert(DCList_link x, DCList_link a, DCList_link b)
{
    assert(x != NULL && a != NULL && b != NULL);
	a->prev = x->prev;      // (1)
	b->next = x;            // (2)
	a->prev->next = a;      // (3)
	b->next->prev = b;      // (4)
}

/**
 * 从链表上删除x节点
 *            ___           ___           ___ 
 *           |   |-------->|   |-------->|   |------>
 *    <------|___|<--------|___|<--------|___|
 *                           ^-x       
 * ==================================================
 *                    .--------------------.
 *                    |(1)                 |
 *            ___     |     ___           _V_ 
 *           |   |----'    |   |-------->|   |------>
 *    <------|___|<--------|___|    .----|___|
 *             A             ^-x    |   
 *             |                    |(2)
 *             '--------------------'
 */
inline
void list_delete(DCList_link x)
{
    assert(x != NULL);
	x->prev->next = x->next;    // (1)
	x->next->prev = x->prev;    // (2)
}

/**
 * 从链表上删除[a,b]节点
 *            ___           ___           ___           ___ 
 *           |   |-------->|   |-------->|   |-------->|   |------>
 *    <------|___|<--------|___|<--------|___|<--------|___|
 *                           ^-a           ^-b         
 * =================================================================
 *                    .----------------------------------.
 *                    |(1)                               |
 *            ___     |     ___           ___           _V_ 
 *           |   |----'    |   |-------->|   |-------->|   |------>
 *    <------|___|<--------|___|<--------|___|    .----|___|
 *             A             ^-a           ^-b    |   
 *             |                                  |(2)
 *             '----------------------------------'
 */
inline
void list_delete(DCList_link a, DCList_link b)
{
    assert(a != NULL && b != NULL);
	a->prev->next = b->next;    // (1)
	b->next->prev = a->prev;    // (2)
}

/**
 * 将t结点移动到x结点前(x, t可以在同一个链表或不同链表上)
 * [nil] <=> [N1] <=> [N2] <=> [N3] <=> ... <=> [Nk-1] <=> [Nk] <=> [Nk+1] <=> ...
 *                              ^-x                         ^-t
 *                               ||
 *                               \/
 *
 * [nil] <=> [N1] <=> [N2] <=> [Nk] <=> [N3] <=> ... <=> [Nk-1] <=> [Nk+1] <=> ... 
 *                              ^-t      ^-x
 */
inline
void list_transfer(DCList_link x, DCList_link t)
{
    assert(x != NULL && t != NULL);

    list_delete(t);            // 移除结点t
    list_insert(x, t);         // 将t结点插入到x结点前
}


/**
 * 将a结点和b结点之间的结点(包括a和b结点)插入到x结点后, 调用者必须保证[a, b]为有效区间
 * [head] <=> [N1] <=> [N2] <=> [N3] <=> ... <=> [NIL]
 *                               ^-x
 *
 * [head] <=> [M1] <=> [M2] <=> [M3] <=> ... <=> [Mk-1] <=> [Mk] <=> [Mk+1] <=> ... <=> [NIL]
 *                      ^-x      ^-a              ^-b        ^-y
 *                                     ||
 *                                     \/
 *
 * [head] <=> [N1] <=> [N2] <=> [M3] <=> ... <=> [Mk-1] <=> [N3] <=> ... <=> [NIL]
 *                               ^-a              ^-b        ^-x
 *
 * [head] <=> [M1] <=> [M2] <=> [Mk] <=> [Mk+1] <=> ... <=> [NIL]
 *                      ^-x      ^-y
 */
inline
void list_transfer_next(SCList_link x, SCList_link a, SCList_link b)
{
    assert(x != NULL && a != NULL && b != NULL);

    list_delete(a, b);
    list_insert(x, a, b);
}

#endif
