<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="WebForm1.aspx.cs" Inherits="WebApplication1.WebForm1" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form method="post" enctype="application/x-www-form-urlencoded" runat="server">
        <div>
            <h2>Parametry GET:</h2>
            <asp:Label ID="lblId" runat="server" Text=""></asp:Label><br />
            <asp:Label ID="lblName" runat="server" Text=""></asp:Label><br />

            <h2>Parametry POST:</h2>
            <asp:Label ID="lblUsername" runat="server" Text=""></asp:Label><br />
            <asp:Label ID="lblEmail" runat="server" Text=""></asp:Label><br />
        </div>
        <div>
            <input type="text" name="username" />
        </div>
        <div>
            <input type="password" name="password" />
        </div>
        <div>
            <asp:Button ID="btnSubmit" runat="server" Text="Wyślij" OnClick="btnSubmit_Click" />
        </div>
    </form>
</body>
</html>
