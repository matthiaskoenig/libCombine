#include <combine/knownformats.h>
#include <combine/util.h>

#include <algorithm>
#include <fstream>

LIBCOMBINE_CPP_NAMESPACE_USE


bool
KnownFormats::isFormat(const std::string &formatKey,
                       const std::string &format)
{
  auto it = mKnownFormats.find(formatKey);

  if (it != mKnownFormats.end())
  {
    auto& knownFormats = it->second;
    auto foundIt = std::find(knownFormats.begin(), knownFormats.end(), format);
    return foundIt != knownFormats.end();
  }


  if (formatKey == "sbml" && format.find("http://identifiers.org/combine.specifications/sbml") == 0)
    return true;
  if (formatKey == "sedml" && format.find("http://identifiers.org/combine.specifications/sed") == 0)
    return true;
  if (formatKey == "sbgn" && format.find("http://identifiers.org/combine.specifications/sbgn") == 0)
    return true;

  return false;

}

std::string
KnownFormats::lookupFormat(const std::string& format)
{
  auto it = mKnownFormats.find(format);

  if (it != mKnownFormats.end())
  {
    auto& knownFormats = it->second;
    return knownFormats.front();
  }
  return "";
}

std::string KnownFormats::guessFormat(const std::string &fileName)
{
  std::string ext = Util::getExtension(fileName);
  if (ext == "xml")
  {
    std::ifstream file(fileName.c_str(), std::ios::binary);
    std::vector<char> buffer(128);
    file.read( &buffer[0], buffer.size() );
    std::string snippet( buffer.begin(), buffer.end() );

    if (snippet.find("<sbml") != std::string::npos)
      return lookupFormat("sbml");
    if (snippet.find("<sedML")!= std::string::npos)
      return lookupFormat("sedml");
    if (snippet.find("<cell")!= std::string::npos)
      return lookupFormat("cellml");
  }

  return lookupFormat(ext);
}

std::vector<std::string>
KnownFormats::getFormatKeys()
{
  std::vector<std::string> result;
  auto it = mKnownFormats.begin();
  for (;it != mKnownFormats.end(); ++it)
    result.push_back(it->first);
  return result;
}


std::map<std::string, std::vector<std::string> >
KnownFormats::mKnownFormats =
{
  {"sbml", {
     "http://identifiers.org/combine.specifications/sbml",
     "http://identifiers.org/combine.specifications/sbml.level-1.version-1",
     "http://identifiers.org/combine.specifications/sbml.level-1.version-2",
     "http://identifiers.org/combine.specifications/sbml.level-2.version-1",
     "http://identifiers.org/combine.specifications/sbml.level-2.version-2",
     "http://identifiers.org/combine.specifications/sbml.level-2.version-3",
     "http://identifiers.org/combine.specifications/sbml.level-2.version-4",
     "http://identifiers.org/combine.specifications/sbml.level-2.version-5",
     "http://identifiers.org/combine.specifications/sbml.level-3.version-1",
     "http://identifiers.org/combine.specifications/sbml.level-3.version-2",
     "http://identifiers.org/combine.specifications/sbml.level-1.version.1",
     "http://identifiers.org/combine.specifications/sbml.level-1.version.2",
     "http://identifiers.org/combine.specifications/sbml.level-2.version.1",
     "http://identifiers.org/combine.specifications/sbml.level-2.version.2",
     "http://identifiers.org/combine.specifications/sbml.level-2.version.3",
     "http://identifiers.org/combine.specifications/sbml.level-2.version.4",
     "http://identifiers.org/combine.specifications/sbml.level-2.version.5",
     "http://identifiers.org/combine.specifications/sbml.level-3.version.1",
     "http://identifiers.org/combine.specifications/sbml.level-3.version.2",
   } },
  {"sedml",
   {
     "http://identifiers.org/combine.specifications/sed-ml",
     "http://identifiers.org/combine.specifications/sedml",
     "http://identifiers.org/combine.specifications/sed-ml.level-1.version-1",
     "http://identifiers.org/combine.specifications/sed-ml.level-1.version-2",
     "http://identifiers.org/combine.specifications/sed-ml.level-1.version-3"
   }},
  {"cellml", {"http://identifiers.org/combine.specifications/cellml" }},
  {"sed-ml",
   {
     "http://identifiers.org/combine.specifications/sed-ml",
     "http://identifiers.org/combine.specifications/sedml",
     "http://identifiers.org/combine.specifications/sed-ml.level-1.version-1",
     "http://identifiers.org/combine.specifications/sed-ml.level-1.version-2",
     "http://identifiers.org/combine.specifications/sed-ml.level-1.version-3"
   }},
  {"sbgn", {"http://identifiers.org/combine.specifications/sbgn" }},
  {"omex", {"http://identifiers.org/combine.specifications/omex-metadata"}},
  {"manifest", {
     "http://identifiers.org/combine.specifications/omex",
     "http://identifiers.org/combine.specifications/omex-manifest",
     "http://identifiers.org/combine.specifications/omex.version-1",
   }},
  {"sedx", {"application/x-sed-ml-archive" }},
  {"png", {"image/png" }},
  {"csv", {"text/csv" }},
  {"323", {"text/h323"}},
  {"acx", {"application/internet-property-stream"}},
  {"ai", {"application/postscript"}},
  {"aif", {"audio/x-aiff"}},
  {"aifc", {"audio/x-aiff"}},
  {"aiff", {"audio/x-aiff"}},
  {"asf", {"video/x-ms-asf"}},
  {"asr", {"video/x-ms-asf"}},
  {"asx", {"video/x-ms-asf"}},
  {"au", {"audio/basic"}},
  {"avi", {"video/x-msvideo"}},
  {"axs", {"application/olescript"}},
  {"bas", {"text/plain"}},
  {"bcpio", {"application/x-bcpio"}},
  {"bin", {"application/octet-stream"}},
  {"bmp", {"image/bmp"}},
  {"c", {"text/plain"}},
  {"cat", {"application/vnd.ms-pkiseccat"}},
  {"cdf", {"application/x-cdf"}},
  {"cer", {"application/x-x509-ca-cert"}},
  {"class", {"application/octet-stream"}},
  {"clp", {"application/x-msclip"}},
  {"cmx", {"image/x-cmx"}},
  {"cod", {"image/cis-cod"}},
  {"cpio", {"application/x-cpio"}},
  {"crd", {"application/x-mscardfile"}},
  {"crl", {"application/pkix-crl"}},
  {"crt", {"application/x-x509-ca-cert"}},
  {"csh", {"application/x-csh"}},
  {"css", {"text/css"}},
  {"dcr", {"application/x-director"}},
  {"der", {"application/x-x509-ca-cert"}},
  {"dir", {"application/x-director"}},
  {"dll", {"application/x-msdownload"}},
  {"dms", {"application/octet-stream"}},
  {"doc", {"application/msword"}},
  {"dot", {"application/msword"}},
  {"dvi", {"application/x-dvi"}},
  {"dxr", {"application/x-director"}},
  {"eps", {"application/postscript"}},
  {"etx", {"text/x-setext"}},
  {"evy", {"application/envoy"}},
  {"exe", {"application/octet-stream"}},
  {"fif", {"application/fractals"}},
  {"flr", {"x-world/x-vrml"}},
  {"gif", {"image/gif"}},
  {"gtar", {"application/x-gtar"}},
  {"gz", {"application/x-gzip"}},
  {"h", {"text/plain"}},
  {"hdf", {"application/x-hdf"}},
  {"hlp", {"application/winhlp"}},
  {"hqx", {"application/mac-binhex40"}},
  {"hta", {"application/hta"}},
  {"htc", {"text/x-component"}},
  {"htm", {"text/html"}},
  {"html", {"text/html"}},
  {"htt", {"text/webviewhtml"}},
  {"ico", {"image/x-icon"}},
  {"ief", {"image/ief"}},
  {"iii", {"application/x-iphone"}},
  {"ins", {"application/x-internet-signup"}},
  {"isp", {"application/x-internet-signup"}},
  {"jfif", {"image/pipeg"}},
  {"jpe", {"image/jpeg"}},
  {"jpeg", {"image/jpeg"}},
  {"jpg", {"image/jpeg"}},
  {"js", {"application/x-javascript"}},
  {"latex", {"application/x-latex"}},
  {"lha", {"application/octet-stream"}},
  {"lsf", {"video/x-la-asf"}},
  {"lsx", {"video/x-la-asf"}},
  {"lzh", {"application/octet-stream"}},
  {"m", {"application/x-matlab"}},
  {"mat", {"application/x-matlab"}},
  {"m13", {"application/x-msmediaview"}},
  {"m14", {"application/x-msmediaview"}},
  {"m3u", {"audio/x-mpegurl"}},
  {"man", {"application/x-troff-man"}},
  {"mdb", {"application/x-msaccess"}},
  {"me", {"application/x-troff-me"}},
  {"mht", {"message/rfc822"}},
  {"mhtml", {"message/rfc822"}},
  {"mid", {"audio/mid"}},
  {"mny", {"application/x-msmoney"}},
  {"mov", {"video/quicktime"}},
  {"movie", {"video/x-sgi-movie"}},
  {"mp2", {"video/mpeg"}},
  {"mp3", {"audio/mpeg"}},
  {"mpa", {"video/mpeg"}},
  {"mpe", {"video/mpeg"}},
  {"mpeg", {"video/mpeg"}},
  {"mpg", {"video/mpeg"}},
  {"mpp", {"application/vnd.ms-project"}},
  {"mpv2", {"video/mpeg"}},
  {"ms", {"application/x-troff-ms"}},
  {"mvb", {"application/x-msmediaview"}},
  {"nws", {"message/rfc822"}},
  {"oda", {"application/oda"}},
  {"p10", {"application/pkcs10"}},
  {"p12", {"application/x-pkcs12"}},
  {"p7b", {"application/x-pkcs7-certificates"}},
  {"p7c", {"application/x-pkcs7-mime"}},
  {"p7m", {"application/x-pkcs7-mime"}},
  {"p7r", {"application/x-pkcs7-certreqresp"}},
  {"p7s", {"application/x-pkcs7-signature"}},
  {"pbm", {"image/x-portable-bitmap"}},
  {"pdf", {"application/pdf"}},
  {"pfx", {"application/x-pkcs12"}},
  {"pgm", {"image/x-portable-graymap"}},
  {"pko", {"application/ynd.ms-pkipko"}},
  {"pma", {"application/x-perfmon"}},
  {"pmc", {"application/x-perfmon"}},
  {"pml", {"application/x-perfmon"}},
  {"pmr", {"application/x-perfmon"}},
  {"pmw", {"application/x-perfmon"}},
  {"pnm", {"image/x-portable-anymap"}},
  {"pot,", {"application/vnd.ms-powerpoint"}},
  {"ppm", {"image/x-portable-pixmap"}},
  {"pps", {"application/vnd.ms-powerpoint"}},
  {"ppt", {"application/vnd.ms-powerpoint"}},
  {"prf", {"application/pics-rules"}},
  {"ps", {"application/postscript"}},
  {"pub", {"application/x-mspublisher"}},
  {"qt", {"video/quicktime"}},
  {"ra", {"audio/x-pn-realaudio"}},
  {"ram", {"audio/x-pn-realaudio"}},
  {"ras", {"image/x-cmu-raster"}},
  {"rgb", {"image/x-rgb"}},
  {"rmi", {"audio/mid"}},
  {"roff", {"application/x-troff"}},
  {"rtf", {"application/rtf"}},
  {"rtx", {"text/richtext"}},
  {"scd", {"application/x-msschedule"}},
  {"sct", {"text/scriptlet"}},
  {"setpay", {"application/set-payment-initiation"}},
  {"setreg", {"application/set-registration-initiation"}},
  {"sh", {"application/x-sh"}},
  {"shar", {"application/x-shar"}},
  {"sit", {"application/x-stuffit"}},
  {"snd", {"audio/basic"}},
  {"spc", {"application/x-pkcs7-certificates"}},
  {"spl", {"application/futuresplash"}},
  {"src", {"application/x-wais-source"}},
  {"sst", {"application/vnd.ms-pkicertstore"}},
  {"stl", {"application/vnd.ms-pkistl"}},
  {"stm", {"text/html"}},
  {"svg", {"image/svg+xml"}},
  {"sv4cpio", {"application/x-sv4cpio"}},
  {"sv4crc", {"application/x-sv4crc"}},
  {"swf", {"application/x-shockwave-flash"}},
  {"t", {"application/x-troff"}},
  {"tar", {"application/x-tar"}},
  {"tcl", {"application/x-tcl"}},
  {"tex", {"application/x-tex"}},
  {"texi", {"application/x-texinfo"}},
  {"texinfo", {"application/x-texinfo"}},
  {"tgz", {"application/x-compressed"}},
  {"tif", {"image/tiff"}},
  {"tiff", {"image/tiff"}},
  {"tr", {"application/x-troff"}},
  {"trm", {"application/x-msterminal"}},
  {"tsv", {"text/tab-separated-values"}},
  {"txt", {"text/plain"}},
  {"uls", {"text/iuls"}},
  {"ustar", {"application/x-ustar"}},
  {"vcf", {"text/x-vcard"}},
  {"vrml", {"x-world/x-vrml"}},
  {"wav", {"audio/x-wav"}},
  {"wcm", {"application/vnd.ms-works"}},
  {"wdb", {"application/vnd.ms-works"}},
  {"wks", {"application/vnd.ms-works"}},
  {"wmf", {"application/x-msmetafile"}},
  {"wps", {"application/vnd.ms-works"}},
  {"wri", {"application/x-mswrite"}},
  {"wrl", {"x-world/x-vrml"}},
  {"wrz", {"x-world/x-vrml"}},
  {"xaf", {"x-world/x-vrml"}},
  {"xbm", {"image/x-xbitmap"}},
  {"xla", {"application/vnd.ms-excel"}},
  {"xlc", {"application/vnd.ms-excel"}},
  {"xlm", {"application/vnd.ms-excel"}},
  {"xls", {"application/vnd.ms-excel"}},
  {"xlt", {"application/vnd.ms-excel"}},
  {"xlw", {"application/vnd.ms-excel"}},
  {"xof", {"x-world/x-vrml"}},
  {"xpm", {"image/x-xpixmap"}},
  {"xwd", {"image/x-xwindowdump"}},
  {"xml", {"application/xml"}},
  {"z", {"application/x-compress"}},
  {"zip", {"application/zip"}},
};