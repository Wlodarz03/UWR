<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="print.aspx.cs" Inherits="Z4.print" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <table border ="1">
    <tr>
        <th>Imie i Nazwisko</th>
        <td><%=(string)Session["name"] + ' ' + (string)Session["surname"] %></td>
        <th>Zajecia</th>
        <td><%=(string)Session["subject"] %></td>
        <th>Nr Listy</th>
        <td><%=(string)Session["setnumber"] %></td>
        <th>Data</th>
        <td><%=(string)Session["date"] %></td>
        
        <!--
        <th>Imie i Nazwisko</th>
        <td><%= Request.QueryString["name"] + ' ' + Request.QueryString["surname"] %></td>
        <th>Zajecia</th>
        <td><%= Request.QueryString["subject"] %></td>
        <th>Nr Listy</th>
        <td><%= Request.QueryString["setnumber"] %></td>
        <th>Data</th>
        <td><%=Request.QueryString["date"] %></td>
        -->
    </tr>
    <tr>
        <%for (int i = 1; i <= 10; i++)
            { %>
           <th style="width:10%">Zad <%=i%></th>
        <%} %>
    </tr>
    <tr>
        <%for (int i = 1; i <= 10; i++){ %>
      <td><%=(int)Session[$"task{i}"].ToString().Length == 0 ? "0" : (string)Session[$"task{i}"]%></td>
        <%} %>
        
    </tr>
</table>
        </div>
    </form>
</body>
</html>
