require 'tk'
require_relative 'game'

# Construye la interfaz Tk y coordina sus eventos con el juego.
class GameWindow
  def initialize
    @juego = Game.new
    @raiz = TkRoot.new

    configurar_ventana
    configurar_eventos
    @campo_entrada.focus
  end

  private

  def configurar_ventana
    @raiz.title('Adivina el Número')
    @raiz.geometry('380x330')
    @raiz.resizable(false, false)

    contenedor = TkFrame.new(@raiz, 'padx' => 24, 'pady' => 20)
    contenedor.pack('fill' => 'both', 'expand' => true)

    TkLabel.new(
      contenedor,
      'text' => 'Adivina el Número',
      'font' => 'Arial 20 bold'
    ).pack('pady' => 6)

    TkLabel.new(
      contenedor,
      'text' => 'Adivina un número del 1 al 100'
    ).pack('pady' => 6)

    @campo_entrada = TkEntry.new(
      contenedor,
      'width' => 22,
      'justify' => 'center'
    )
    @campo_entrada.pack('pady' => 8)

    @boton_adivinar = TkButton.new(
      contenedor,
      'text' => 'Adivinar',
      'width' => 20
    )
    @boton_adivinar.pack('pady' => 6, 'ipady' => 4)

    @etiqueta_resultado = TkLabel.new(
      contenedor,
      'text' => '',
      'width' => 36,
      'height' => 2
    )
    @etiqueta_resultado.pack('pady' => 4)

    @etiqueta_intentos = TkLabel.new(
      contenedor,
      'text' => 'Intentos: 0'
    )
    @etiqueta_intentos.pack('pady' => 4)

    @boton_reiniciar = TkButton.new(
      contenedor,
      'text' => 'Reiniciar',
      'width' => 20
    )
    @boton_reiniciar.pack('pady' => 6, 'ipady' => 4)
  end

  def configurar_eventos
    @boton_adivinar.configure('command' => proc { procesar_intento })
    @campo_entrada.bind('Return', proc { procesar_intento })
    @boton_reiniciar.configure('command' => proc { reiniciar_juego })
  end

  def procesar_intento
    return if @juego.terminado?

    numero = validar_entrada
    return if numero.nil?

    resultado = @juego.comprobar_numero(numero)
    @etiqueta_resultado.configure('text' => resultado)
    @etiqueta_intentos.configure('text' => "Intentos: #{@juego.intentos}")

    if resultado == '¡Correcto!'
      finalizar_juego
      return
    end

    @campo_entrada.focus
  end

  def validar_entrada
    entrada = @campo_entrada.get.strip

    if entrada.empty?
      mostrar_error_validacion('Ingresa un número.')
      return nil
    end

    unless entrada.match?(/\A[+-]?[0-9]+\z/)
      mostrar_error_validacion('Ingresa solamente números.')
      return nil
    end

    begin
      numero = Integer(entrada, 10)
    rescue ArgumentError
      mostrar_error_validacion('El número debe estar entre 1 y 100.')
      return nil
    end

    unless numero.between?(Game::NUMERO_MINIMO, Game::NUMERO_MAXIMO)
      mostrar_error_validacion('El número debe estar entre 1 y 100.')
      return nil
    end

    numero
  end

  def mostrar_error_validacion(mensaje)
    @etiqueta_resultado.configure('text' => mensaje)
    @campo_entrada.focus
  end

  def finalizar_juego
    @campo_entrada.configure('state' => 'disabled')
    @boton_adivinar.configure('state' => 'disabled')
  end

  def reiniciar_juego
    @juego.reiniciar
    @campo_entrada.configure('state' => 'normal')
    @boton_adivinar.configure('state' => 'normal')
    @campo_entrada.delete(0, 'end')
    @etiqueta_resultado.configure('text' => '')
    @etiqueta_intentos.configure('text' => 'Intentos: 0')
    @campo_entrada.focus
  end
end
