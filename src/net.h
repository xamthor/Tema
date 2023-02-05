#ifndef __NET_H__
#define __NET_H__

void netInit();
void netTerm();
void httpInit();
void httpTerm();

void download(const char *url, const char *dest);

#endif
