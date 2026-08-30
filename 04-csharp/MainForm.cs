using System.Drawing;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace AdivinaNumero;

/// <summary>Construye la interfaz WinForms y coordina sus eventos con el juego.</summary>
public sealed class MainForm : Form
{
    private readonly Game game;
    private readonly TextBox guessTextBox;
    private readonly Button guessButton;
    private readonly Button resetButton;
    private readonly Label resultLabel;
    private readonly Label attemptsLabel;
    private bool gameFinished;

    public MainForm()
    {
        game = new Game();
        guessTextBox = new TextBox();
        guessButton = new Button();
        resetButton = new Button();
        resultLabel = new Label();
        attemptsLabel = new Label();
        gameFinished = false;

        ConfigurarVentana();
        ConfigurarEventos();
    }

    private void ConfigurarVentana()
    {
        Text = "Adivina el Número";
        ClientSize = new Size(380, 305);
        FormBorderStyle = FormBorderStyle.FixedSingle;
        MaximizeBox = false;
        StartPosition = FormStartPosition.CenterScreen;

        Label titleLabel = new Label
        {
            Text = "Adivina el Número",
            Font = new Font("Segoe UI", 16, FontStyle.Bold),
            Location = new Point(24, 18),
            Size = new Size(332, 36),
            TextAlign = ContentAlignment.MiddleCenter
        };

        Label instructionsLabel = new Label
        {
            Text = "Adivina un número del 1 al 100",
            Location = new Point(24, 60),
            Size = new Size(332, 24),
            TextAlign = ContentAlignment.MiddleCenter
        };

        guessTextBox.Location = new Point(100, 94);
        guessTextBox.Size = new Size(180, 27);
        guessTextBox.TextAlign = HorizontalAlignment.Center;

        guessButton.Text = "Adivinar";
        guessButton.Location = new Point(110, 132);
        guessButton.Size = new Size(160, 34);

        resultLabel.Location = new Point(24, 178);
        resultLabel.Size = new Size(332, 24);
        resultLabel.TextAlign = ContentAlignment.MiddleCenter;

        attemptsLabel.Text = "Intentos: 0";
        attemptsLabel.Location = new Point(24, 210);
        attemptsLabel.Size = new Size(332, 24);
        attemptsLabel.TextAlign = ContentAlignment.MiddleCenter;

        resetButton.Text = "Reiniciar";
        resetButton.Location = new Point(110, 246);
        resetButton.Size = new Size(160, 34);

        AcceptButton = guessButton;

        Controls.AddRange(new Control[]
        {
            titleLabel,
            instructionsLabel,
            guessTextBox,
            guessButton,
            resultLabel,
            attemptsLabel,
            resetButton
        });
    }

    private void ConfigurarEventos()
    {
        guessButton.Click += (_, _) => ProcesarIntento();
        resetButton.Click += (_, _) => ReiniciarJuego();
        Shown += (_, _) => guessTextBox.Focus();
    }

    private void ProcesarIntento()
    {
        if (gameFinished)
        {
            return;
        }

        int? number = ValidarEntrada();

        if (number is null)
        {
            return;
        }

        string result = game.ComprobarNumero(number.Value);
        resultLabel.Text = result;
        attemptsLabel.Text = $"Intentos: {game.Intentos}";

        if (result == "¡Correcto!")
        {
            FinalizarJuego();
            return;
        }

        guessTextBox.SelectAll();
        guessTextBox.Focus();
    }

    private int? ValidarEntrada()
    {
        string input = guessTextBox.Text.Trim();

        if (input.Length == 0)
        {
            MostrarErrorValidacion("Ingresa un número.");
            return null;
        }

        if (!Regex.IsMatch(input, @"^[+-]?[0-9]+$"))
        {
            MostrarErrorValidacion("Ingresa solamente números.");
            return null;
        }

        if (!int.TryParse(input, out int number))
        {
            MostrarErrorValidacion("El número debe estar entre 1 y 100.");
            return null;
        }

        if (number < Game.MinNumber || number > Game.MaxNumber)
        {
            MostrarErrorValidacion("El número debe estar entre 1 y 100.");
            return null;
        }

        return number;
    }

    private void MostrarErrorValidacion(string message)
    {
        resultLabel.Text = message;
        guessTextBox.Focus();
    }

    private void FinalizarJuego()
    {
        gameFinished = true;
        guessTextBox.Enabled = false;
        guessButton.Enabled = false;
    }

    private void ReiniciarJuego()
    {
        game.Reiniciar();
        gameFinished = false;

        guessTextBox.Clear();
        guessTextBox.Enabled = true;
        guessButton.Enabled = true;
        resultLabel.Text = string.Empty;
        attemptsLabel.Text = "Intentos: 0";
        guessTextBox.Focus();
    }
}
