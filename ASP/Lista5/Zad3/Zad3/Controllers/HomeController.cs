using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Web.Mvc;
using System.Web.UI.WebControls;
using System.Xml.Linq;

namespace Zad3
    .Controllers
{
    public class HomeController : Controller
    {
        [HttpGet]
        public ActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public ActionResult Upload()
        {
            if (Request.Files.Count == 0 || Request.Files[0] == null)
            {
                return new HttpStatusCodeResult(400, "Prosze przeslac plik.");
            }

            var file = Request.Files[0];

            string fileName = Path.GetFileName(file.FileName);
            long fileSize = file.ContentLength;
            ushort checksum = 0;

            using (var stream = file.InputStream)
            {
                int readByte;
                while ((readByte = stream.ReadByte()) != -1)
                {
                    checksum = (ushort)((checksum + readByte) % 0xFFFF);
                }
            }
            string xmlResponse = new XDocument(
                new XElement("opis",
                    new XElement("nazwa", fileName),
                    new XElement("rozmiar", fileSize),
                    new XElement("sygnatura", checksum)
                )
            ).ToString();

            Response.AddHeader("Content-Disposition", $"attachment; filename*=UTF-8''{Url.Encode($"{fileName}_metadata.xml")}");

            return Content(xmlResponse, "application/xml", Encoding.UTF8);


        }
    }
}