#define BROWSER "chromium"
#define EDITOR "nvim"
#define MEDIA "mpv"
static Rule protocols[] = {
  {"http://"                 ,BROWSER                                           ,false} ,
  {"https://"                ,BROWSER                                           ,false} ,
  {"dvd://"                  ,MEDIA                                             ,true } ,
  {"cdda://"                 ,MEDIA                                             ,true } ,
  {"mumble://"               ,"mumble"                                          ,false} ,
  {"steam://"                ,"steam"                                           ,false} ,
  {"magnet:?"                ,"/home/nokkasiili/Projects/Scripts/magnet.sh"     ,false} ,
};

static Rule mimes[] = {
  {"text/html"               ,BROWSER                                           ,false} ,
  {"text"                    ,EDITOR                                            ,true } ,
  {"video"                   ,MEDIA                                             ,true } ,
  {"audio"                   ,MEDIA                                             ,true } ,
  {"application/octet-stream",MEDIA                                             ,true } ,
  {"image"                   ,"sxiv"                                            ,false} ,
  {"inode"                   ,"/home/nokkasiili/Projects/Scripts/openfolder.sh" ,false} ,
};
