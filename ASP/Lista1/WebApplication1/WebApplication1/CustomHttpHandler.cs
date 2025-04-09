using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services.Description;

namespace WebApplication1
{
    public class CustomHttpHandler : IHttpHandler
    {
        public bool IsReusable => true;

        /// <summary>
        /// ?
        /// </summary>
        /// <param name="context"></param>

        public void ProcessRequest(HttpContext context)
        {
            context.Response.AppendHeader("Content-type", "text/plain");

            // Pełny adres bieżącego żądania
            context.Response.Write("handler obsługuje " + context.Request.Url +"\n");

            // Nagłówki HTTP
            context.Response.Write("Nagłówki HTTP:\n");
            foreach (var header in context.Request.Headers.AllKeys)
            {
                context.Response.Write($"{header}: {context.Request.Headers[header]}\n");
            }
            context.Response.Write("\n");

            // Rodzaj żądania (HTTP verb)
            context.Response.Write("Rodzaj żądania (HTTP verb): " + context.Request.HttpMethod + "\n");

            // Treść żądania (jeśli żądanie było typu POST i zawierało niepustą treść)

            if (context.Request.HttpMethod == "POST" && context.Request.ContentLength > 0)
            {
                context.Request.InputStream.Position = 0;
                context.Response.Write("Treść żadania POST: ");
                using (var reader = new System.IO.StreamReader(context.Request.InputStream))
                {
                    string requestBody = reader.ReadToEnd();
                    context.Response.Write(requestBody);
                }
            }
            else
            {
                context.Response.Write("Brak żądania typu POST lub brak treści");
            }
            context.Response.End();
        }
    }
}