using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Zad7
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void UploadButton_Click(object sender, EventArgs e)
        {
            if (!FileUploader.HasFile)
            {
                Response.Write("Nie wybrano pliku");
                return;
            }

            // informacje o pliku
            var fileName = FileUploader.FileName;
            var fileSize = FileUploader.PostedFile.ContentLength;
            var fileSignature = Calculate(FileUploader.PostedFile.InputStream);

            // generowanie XML w pamięci
            var xmlContent = $"<opis>\n<nazwa>{fileName}</nazwa>\n<rozmiar>{fileSize}</rozmiar>\n<sygnatura>{fileSignature}</sygnatura>\n</opis>";

            // ustawienie nagłówków odpowiedzi
            var contentDisposition = $"attachment; filename*=UTF-8''{Uri.EscapeDataString("opis_" + fileName)}.xml";
            Response.Clear();
            Response.ContentType = "application/xml";
            Response.AddHeader("Content-Disposition", contentDisposition);

            // Wysłanie odpowiedzi bez zapisu na dysku serwera
            byte[] xmlBytes = Encoding.UTF8.GetBytes(xmlContent);
            Response.BinaryWrite(xmlBytes);
            Response.End();
        }

        private int Calculate(System.IO.Stream fileStream)
        {
            int sum = 0;
            int byteRead;
            while ((byteRead = fileStream.ReadByte()) != -1)
            {
                sum += byteRead;
            }
            return sum % 0xFFFF;
        }
        protected void Page_Load(object sender, EventArgs e)
        {
            // Zadanie 4 lista 4 - odczyt danych
            string siteTitle = ConfigurationManager.AppSettings["SiteTitle"];
            string connectionString = ConfigurationManager.ConnectionStrings["DefaultConnection"].ConnectionString;
            Response.Write($"Site Title: {siteTitle}<br/>");
            Response.Write($"Connection String: {connectionString}");

        }
    }
}