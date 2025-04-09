<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="start.aspx.cs" Inherits="Z4.start" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>Pasek Zgloszenia zadan</title>
    <script src="https://code.jquery.com/jquery-3.7.1.min.js"></script>
</head>

<body>
    <form id="form1" runat="server">
        <div>
            <h3>Deklaracja zadan</h3>
            Imie:
            <asp:TextBox ID="txtName" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server"
                ControlToValidate="txtName"
                ErrorMessage="Name is a required field."
                ForeColor="Red">
            </asp:RequiredFieldValidator>
            <br />
            <br />

            Nazwisko:
            <asp:TextBox ID="txtSurname" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server"
                ControlToValidate="txtSurname"
                ErrorMessage="Surname is a required field."
                ForeColor="Red">
            </asp:RequiredFieldValidator>
            <br />
            <br />

            Nazwa Przedmiotu:
            <asp:TextBox ID="txtSubject" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server"
                ControlToValidate="txtSubject"
                ErrorMessage="Subject name is a required field."
                ForeColor="Red">
            </asp:RequiredFieldValidator>
            <br />
            <br />

            Numer Zestawu:
            <asp:TextBox ID="txtSetNumber" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator ID="RequiredFieldValidator4" runat="server"
                ControlToValidate="txtSetNumber"
                ErrorMessage="Set number is a required field."
                ForeColor="Red">
            </asp:RequiredFieldValidator>
            <br />
            <br />

            Data:
            <asp:TextBox ID="txtDate" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator ID="RequiredFieldValidator5" runat="server"
                ControlToValidate="txtDate"
                ErrorMessage="Date is a required field."
                ForeColor="Red">
            </asp:RequiredFieldValidator>
            <br />
            <br />

        </div>

        <div class="task" id="TaskPanel" runat="server">
            <br />
        </div>

        <asp:Button ID="btnSubmit" Text="Potwierdz deklaracje" runat="server" OnClick="btnSubmit_Click" />
    </form>
</body>
</html>

