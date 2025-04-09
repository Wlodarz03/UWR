using System;
using System.Collections.Generic;
using System.EnterpriseServices;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApplication1
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            // dodanie ciastka
            var cookie = new HttpCookie("username");
            cookie.Value = "asp";
            this.Response.Cookies.Add(cookie);

            // odczytanie ciastka
            var cookie2 = this.Response.Cookies[0];

            // usuniecie ciastka
            //cookie.Expires = DateTime.Now.AddHours(-2); // odeslac ciastko z data ważności z przeszłości


            // wiarygodnie - spróbować odczytać ciastko jak się nie da to nie obsługuje
            // naiwnie - w przeglądarce zbadaj -> Application -> Cookies
            // jak jest tam jakieś ciastko to obsługuje

            if (Request.HttpMethod == "GET")
            {
                lblId.Text = "ID: " + Request.QueryString["id"];
                lblName.Text = "Name: " + Request.QueryString["name"];
            }

            // Zadanie 4

            // Ustawiamy licznik aktywnych użytkowników
            Application["ActiveUsers"] = 0;

            // Zwiększamy licznik aktywnych użytkowników
            Application["ActiveUsers"] = (int)Application["ActiveUsers"] + 1;

            // nazwa użytownika w sesji
            Session["UserName"] = "asp";

            // odczytujemy nazwe użytownika w sesji
            string userName = (string)Session["UserName"];

            // Przechowujemy dane na czas bieżącego żądania
            Context.Items["RequestStartTime"] = DateTime.Now;

            // odczytujemy czas rozpoczęcia żądania
            DateTime startTime = (DateTime)Context.Items["RequestStartTime"];


        }
        protected void Page_Unload(object sender, EventArgs e)
        {
            // Zmniejszamy licznik aktywnych użytkowników, kiedy użytkownik opuszcza stronę
            Application["ActiveUsers"] = (int)Application["ActiveUsers"] - 1;
        }

        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            lblUsername.Text = "Username: " + Request.Form["username"];
            lblEmail.Text = "Password: " + Request.Form["password"];
        }
    }
}