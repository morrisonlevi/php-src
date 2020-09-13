
set (PHP_STANDARD_SOURCES
    array.c
    assert.c
    base64.c
    basic_functions.c
    browscap.c
    crc32.c
    crc32_x86.c
    credits.c
    crypt.c
    css.c
    datetime.c
    dir.c
    dl.c
    dns.c
    exec.c
    file.c
    filestat.c
    filters.c
    flock_compat.c
    formatted_print.c
    fsock.c
    ftok.c
    ftp_fopen_wrapper.c
    head.c
    hrtime.c
    html.c
    http.c
    http_fopen_wrapper.c
    image.c
    incomplete_class.c
    info.c
    iptc.c
    lcg.c
    levenshtein.c
    link.c
    mail.c
    math.c
    md5.c
    metaphone.c
    microtime.c
    mt_rand.c
    net.c
    pack.c
    pageinfo.c
    password.c
    php_fopen_wrapper.c
    proc_open.c
    quot_print.c
    rand.c
    random.c
    scanf.c
    sha1.c
    soundex.c
    streamsfuncs.c
    string.c
    strnatcmp.c
    syslog.c
    type.c
    uniqid.c
    url.c
    url_scanner_ex.c
    user_filters.c
    uuencode.c
    var.c
    var_unserializer.c
    versioning.c
)

#[[ todo: should this be STATIC? My inclination is yes but it has a ZEND_API
    function. If other extensions use this dependency then we get multiple
    things linking in the same static libary (doesn't work, that I know of),
    OR we have to allow undefined symbols to not cause link errors. I don't
    like that option as undefined symbols are almost always an error, and it
    also causes a performance hit to look the symbols up at runtime.
]]
add_library(Standard SHARED ${PHP_STANDARD_SOURCES})
target_link_libraries(Standard PUBLIC Zend)

