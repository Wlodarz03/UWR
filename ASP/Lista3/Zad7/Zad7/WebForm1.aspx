<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="WebForm1.aspx.cs" Inherits="Zad7.WebForm1" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Przesyłanie pliku</title>
</head>
<body>
    <form id="form1" runat="server" enctype="multipart/form-data">
        <asp:FileUpload ID="FileUploader" runat="server" />
        <asp:Button ID="UploadButton" runat="server" Text="Wyślij plik" OnClick="UploadButton_Click" />
    </form>
</body>
</html>
