/*
 * PuTTY version numbering
 */

#define STR1(x) #x
#define STR(x) STR1(x)

#if defined SNAPSHOT

char ver[] = "�������� " STR(SNAPSHOT);
char sshver[] = "sshX-����-" STR(SNAPSHOT);

#elif defined RELEASE

char ver[] = "������ " STR(RELEASE);
char sshver[] = "sshX-������-" STR(RELEASE);

#else

char ver[] = "δ��ȷ�ϱ����, " __DATE__ " " __TIME__;
char sshver[] = "sshX-����: " __DATE__ " " __TIME__;

#endif

/*
 * SSH local version string MUST be under 40 characters. Here's a
 * compile time assertion to verify this.
 */
enum { vorpal_sword = 1 / (sizeof(sshver) <= 40) };
