using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml.Linq;

namespace Z4
{
    public partial class start : System.Web.UI.Page
    {

        protected void Page_Load(object sender, EventArgs e)
        {
            for (int i = 1; i <= 10; i++)
            {
                TextBox txtTask = new TextBox
                {
                    ID = $"txtTask{i}",
                    TextMode = TextBoxMode.Number
                };

                TaskPanel.Controls.Add(new LiteralControl($"Zadanie {i}: "));
                TaskPanel.Controls.Add(txtTask);

                TaskPanel.Controls.Add(new LiteralControl("<br />"));
            }
        }

        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            Session["name"] = txtName.Text;
            Session["surname"] = txtSurname.Text;
            Session["subject"] = txtSubject.Text;
            Session["setnumber"] = txtSetNumber.Text;
            Session["date"] = txtDate.Text;


            for (int i = 1; i <= 10; i++)
            {
                Session[$"task{i}"] = Request.Form[$"txtTask{i}"];
            }
            Response.Redirect("print.aspx");
            //Response.Redirect($"print.aspx?name={HttpUtility.UrlEncode(txtName.Text)}&surname={HttpUtility.UrlEncode(txtSurname.Text)}&subject={HttpUtility.UrlEncode(txtSubject.Text)}&setnumber={HttpUtility.UrlEncode(txtSetNumber.Text)}&date={HttpUtility.UrlEncode(txtDate.Text)}");

        }
    }
}