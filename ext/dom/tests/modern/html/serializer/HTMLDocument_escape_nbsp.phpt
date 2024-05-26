--TEST--
Dom\HTMLDocument serialization escape nbsp
--EXTENSIONS--
dom
--FILE--
<?php

$dom = Dom\HTMLDocument::createFromString("<p>these must transform: \xc2\xa0\xc2\xa0 but these not: \xa0|\xc2...</p><br>", LIBXML_NOERROR);
echo $dom->saveHtml();

?>
--EXPECT--
<html><head></head><body><p>these must transform: &nbsp;&nbsp; but these not: �|�...</p><br></body></html>
