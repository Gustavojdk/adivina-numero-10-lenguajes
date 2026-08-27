using System.Drawing;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace AdivinaNumero;

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

        ConfigureWindow();
        ConfigureEvents();
    }

    private void ConfigureWindow()
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

    private void ConfigureEvents()
    {
        guessButton.Click += (_, _) => SubmitGuess();
        resetButton.Click += (_, _) => ResetGame();
        Shown += (_, _) => guessTextBox.Focus();
    }

    private void SubmitGuess()
    {
        if (gameFinished)
        {
            return;
        }

        string input = guessTextBox.Text.Trim();

        if (input.Length == 0)
        {
            resultLabel.Text = "Ingresa un número.";
            guessTextBox.Focus();
            return;
        }

        if (!Regex.IsMatch(input, @"^[+-]?[0-9]+$"))
        {
            resultLabel.Text = "Ingresa solamente números.";
            guessTextBox.Focus();
            return;
        }

        if (!int.TryParse(input, out int number))
        {
            resultLabel.Text = "El número debe estar entre 1 y 100.";
            guessTextBox.Focus();
            return;
        }

        if (number < Game.MinNumber || number > Game.MaxNumber)
        {
            resultLabel.Text = "El número debe estar entre 1 y 100.";
            guessTextBox.Focus();
            return;
        }

        string result = game.CheckGuess(number);
        resultLabel.Text = result;
        attemptsLabel.Text = $"Intentos: {game.Attempts}";

        if (result == "¡Correcto!")
        {
            gameFinished = true;
            guessTextBox.Enabled = false;
            guessButton.Enabled = false;
            return;
        }

        guessTextBox.SelectAll();
        guessTextBox.Focus();
    }

    private void ResetGame()
    {
        game.Reset();
        gameFinished = false;

        guessTextBox.Clear();
        guessTextBox.Enabled = true;
        guessButton.Enabled = true;
        resultLabel.Text = string.Empty;
        attemptsLabel.Text = "Intentos: 0";
        guessTextBox.Focus();
    }
}
