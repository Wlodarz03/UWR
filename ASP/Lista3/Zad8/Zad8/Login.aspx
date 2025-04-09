<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="Zad8.WebForm2" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <h2>Zaloguj sie</h2>
            Login: 
            <asp:TextBox ID="TextBoxUsername" runat="server"></asp:TextBox><br />
            Hasło:
            <asp:TextBox ID="TextBoxPassword" runat="server" TextMode="Password"></asp:TextBox><br />
            <asp:Button ID="ButtonLogin" runat="server" Text="Zaloguj" OnClick="ButtonLogin_Click" />
            <asp:Label ID="LabelMessage" runat="server" ForeColor="Red"></asp:Label>
        </div>
    </form>
</body>
</html>
