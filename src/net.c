#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <psp2/io/fcntl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/net/http.h>
#include <psp2/sysmodule.h>

// curl includes
#include <stdlib.h>
#include <curl/curl.h>
#include <psp2/libssl.h>

#include <psp2/io/stat.h> 
#include <psp2/display.h>

#define HTTP_SUCCESS 	1
#define HTTP_FAILED	 	0
#define HTTP_USER_AGENT "Mozilla/5.0 (PLAYSTATION VITA; 1.00)"

void netInit() {
	// psvDebugScreenPrintf("Loading module SCE_SYSMODULE_NET\n");
	sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
	
	// psvDebugScreenPrintf("Running sceNetInit\n");
	SceNetInitParam netInitParam;
	int size = (16 * 1024);
	netInitParam.memory = malloc(size);
	netInitParam.size = size;
	netInitParam.flags = 0;
	sceNetInit(&netInitParam);
    curl_global_init(CURL_GLOBAL_ALL);
	// psvDebugScreenPrintf("Running sceNetCtlInit\n");
	sceNetCtlInit();
}

void netTerm() {
	// psvDebugScreenPrintf("Running sceNetCtlTerm\n");
	sceNetCtlTerm();

	// psvDebugScreenPrintf("Running sceNetTerm\n");
	sceNetTerm();

	// psvDebugScreenPrintf("Unloading module SCE_SYSMODULE_NET\n");
	sceSysmoduleUnloadModule(SCE_SYSMODULE_NET);
}

void httpInit() {
	// psvDebugScreenPrintf("Loading module SCE_SYSMODULE_HTTP\n");
	sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);

	// psvDebugScreenPrintf("Running sceHttpInit\n");
	sceHttpInit(4*1024*1024);
}

void httpTerm() {
    curl_global_cleanup();
	// psvDebugScreenPrintf("Running sceHttpTerm\n");
	sceHttpTerm();

	// psvDebugScreenPrintf("Unloading module SCE_SYSMODULE_HTTP\n");
	sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTP);
}

void download(const char *url, const char *local_dst) {
    CURL *curl;
    CURLcode res;
    FILE *fd;

    curl = curl_easy_init();

    fd = fopen(local_dst, "wb");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    // Set user agent string
    curl_easy_setopt(curl, CURLOPT_USERAGENT, HTTP_USER_AGENT);
    // not sure how to use this when enabled
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    // not sure how to use this when enabled
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    // Set SSL VERSION to TLS 1.2
    curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
    // Set timeout for the connection to build
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    // Follow redirects (?)
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    // The function that will be used to write the data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
    // The data filedescriptor which will be written to
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd);
    // maximum number of redirects allowed
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 20L);
    // Fail the request if the HTTP code returned is equal to or larger than 400
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
    // request using SSL for the FTP transfer if available
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

    // Perform the request
    res = curl_easy_perform(curl);
    // close filedescriptor
    fclose(fd);
    // cleanup
    curl_easy_cleanup(curl);

}