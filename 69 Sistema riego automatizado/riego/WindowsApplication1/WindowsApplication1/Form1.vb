Imports System.IO.Ports

Public Class Form_Pricipal
    Dim Recibidos As String
    Public Sub New()
        InitializeComponent()
        ' Abrir puerto mientras se ejecute la aplicación
        If Not SerialPort1.IsOpen Then
            Try
                SerialPort1.Open()
            Catch ex As System.Exception
                MessageBox.Show(ex.ToString())
            End Try
        End If
        AddHandler SerialPort1.DataReceived, AddressOf Recepcion
    End Sub
    Private Sub Recepcion(ByVal sender As Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs)
        Recibidos += SerialPort1.ReadExisting()
        Me.Invoke(New EventHandler(AddressOf Actualizar))
    End Sub
    Private Sub Actualizar(ByVal s As Object, ByVal e As EventArgs)
        TextBox1.Text = Recibidos
    End Sub




    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dim mBuffer As Byte() = New Byte(0) {}
        mBuffer(0) = &H31 'ASCII  "1".
        SerialPort1.Write(mBuffer, 0, mBuffer.Length)
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Dim mBuffer As Byte() = New Byte(0) {}
        mBuffer(0) = &H32 'ASCII  "1".
        SerialPort1.Write(mBuffer, 0, mBuffer.Length)
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        Dim mBuffer As Byte() = New Byte(0) {}
        mBuffer(0) = &H33 'ASCII  "1".
        SerialPort1.Write(mBuffer, 0, mBuffer.Length)
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        Dim mBuffer As Byte() = New Byte(0) {}
        mBuffer(0) = &H34 'ASCII  "1".
        SerialPort1.Write(mBuffer, 0, mBuffer.Length)
    End Sub

    
    
    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        Dim mBuffer As Byte() = New Byte(0) {}
        mBuffer(0) = &H35 'ASCII  "1".
        SerialPort1.Write(mBuffer, 0, mBuffer.Length)
    End Sub

    Private Sub Button6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button6.Click
        Dim mBuffer As Byte() = New Byte(0) {}
        mBuffer(0) = &H36 'ASCII  "1".
        SerialPort1.Write(mBuffer, 0, mBuffer.Length)
    End Sub

    Private Sub Button7_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button7.Click
        Dim mBuffer As Byte() = New Byte(0) {}
        mBuffer(0) = &H37 'ASCII  "1".
        SerialPort1.Write(mBuffer, 0, mBuffer.Length)
    End Sub

    Private Sub Button8_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button8.Click
        Dim mBuffer As Byte() = New Byte(0) {}
        mBuffer(0) = &H38 'ASCII  "1".
        SerialPort1.Write(mBuffer, 0, mBuffer.Length)
    End Sub

    Private Sub Button9_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        PrintDialog(TextBox1.Text);
        PrintPreviewDialog1(TextBox1.Text);
    End Sub
End Class
