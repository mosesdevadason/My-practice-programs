#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

/* Data structure to store time in seconds and micro-seconds */
typedef struct __os_time_t
{
    long int sec;
    long int usec;
} os_time_t;

/* Node to store a timeout in the timeout linked list */
typedef struct __timeout_t
{
    os_time_t time;
    struct __timeout_t *next;
} timeout_t;

/* Timeout linked list head */
static timeout_t *timeout_head = NULL;

/* Get current time */
int os_get_time(os_time_t *t)
{
    int rc = 0;
    struct timeval tv = {0};
    rc = gettimeofday(&tv, NULL);
    t->sec = tv.tv_sec;
    t->usec = tv.tv_usec;
    printf("%s:%s:%d: sec : %ld, usec : %ld\n", __FILE__, __func__, __LINE__,
           t->sec, t->usec);
    return rc;
}

/* Checks whether time a is lesser than time b. Returns true if so */
static inline uint32_t os_time_before(os_time_t *a, os_time_t *b)
{
    return ((a->sec < b->sec) || ((a->sec == b->sec) && (a->usec < b->usec)));
}

static inline void os_time_sub(os_time_t *a, os_time_t *b, os_time_t *res)
{
    res->sec = a->sec - b->sec;
    res->usec = a->usec - b->usec;
    if (res->usec < 0) {
        res->sec--;
        res->usec = res->usec + 1000000;
    }
    printf("%s:%s:%d: sec : %ld, usec : %ld\n", __FILE__, __func__, __LINE__,
           res->sec, res->usec);
}

/* Register a timeout 
 * Adds a node in the timeout linked list 
 * The timeout would occur at the time represented by sec and usec from now */
int register_timeout(long int sec, long int usec)
{
    timeout_t *timeout = NULL;
    timeout_t *tmp = NULL;
    timeout_t *prev = NULL;

    if (NULL == (timeout = malloc(sizeof(timeout_t)))) {
        printf("%s:%s:%d: malloc() failed\n", __FILE__, __func__, __LINE__);
        return -1;
    }
    /* Add sec and usec to the current time and add the node to linked list */
    os_get_time(&(timeout->time));
    timeout->time.sec = timeout->time.sec + sec;
    timeout->time.usec = timeout->time.usec + sec;
    /* If usec is greater than 100000 add 1 to sec and subtract 1000000 from
     * usec */
    while (timeout->time.usec >= 1000000) {
        timeout->time.sec++;
        timeout->time.usec = timeout->time.usec - 1000000;
    }

    timeout->next = NULL;
    /* If this is the first timeout, make the node the head of the list */
    if (NULL == timeout_head) {
        timeout_head = timeout;
        return 0;
    }

    /* Insert nodes in sorted order */
    tmp = timeout_head;
    while (NULL != tmp) {
        if (os_time_before(&(timeout->time), &(tmp->time))) {
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    /* If the time value is less than the first node(head) */
    if (NULL == prev) {
        timeout->next = timeout_head;
        timeout_head = timeout;
    } else {
        timeout->next = prev->next;
        prev->next = timeout;
    }

    printf("%s:%s:%d: Inserted new timeout. sec: %ld, usec: %ld\n",
    __FILE__,
           __func__, __LINE__, timeout->time.sec, timeout->time.usec);

    return 0;
}

void run_timer(void)
{
    struct timeval _tv;
    os_time_t tv, now;
    int rc = 0;

    /* The timeout in the head node is given to select as a timeout */
    while (NULL != timeout_head) {
        /* check if the current time is lesser than the timeout */
        os_get_time(&now);
        if (os_time_before(&now, &(timeout_head->time))) {
            printf("-------------------------------------------------------\n");
            printf("Timeout for select.\n");
            os_time_sub(&(timeout_head->time), &now, &tv);
            printf("-------------------------------------------------------\n");
        } else {
            /* If current time is greater than the first timeout (head) set sec
             * and usec as 0 */
            tv.sec = tv.usec = 0;
        }
        _tv.tv_sec = tv.sec;
        _tv.tv_usec = tv.usec;
        rc = select(0, NULL, NULL, NULL, &_tv);
        /* Select has unblocked because an event has occured 
         * In our case the only events are timeouts */
        if ((rc < 0) && (errno != EINTR) && (errno != 0)) {
            /* If return value is -1 and errno is valid and not EINTR throw
             * error log EINTR means a signal has been caught. So it is not an
             * error case */
            perror("select\n");
            return;
        }

        /* Check if timeout has occured */
        timeout_t *tmp;
        if (!os_time_before(&now, &(timeout_head->time))) {
            tmp = timeout_head;
            printf("%s:%s:%d: Timeout occured. sec: %ld, usec: %ld\n",
            __FILE__,
                   __func__, __LINE__, tmp->time.sec, tmp->time.usec);
            timeout_head = timeout_head->next;
            free(tmp);
        }
    }
}

int main(int argc, char *argv[])
{
    /* Add calls to register_timeout(sec, usec) for more timeouts */
    register_timeout(10, 0);
    register_timeout(15, 0);
    register_timeout(17, 0);
    register_timeout(20, 0);
    printf("===============================================================\n");
    printf("                 --------TIMER START---------                  \n");
    printf("===============================================================\n");
    run_timer();
    printf("===============================================================\n");
    printf("                 --------TIMER  STOP---------                  \n");
    printf("===============================================================\n");

    return EXIT_SUCCESS;
}
