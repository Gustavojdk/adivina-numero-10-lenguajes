# Mantiene la lógica y el estado de una partida.
class Game
  NUMERO_MINIMO = 1
  NUMERO_MAXIMO = 100

  attr_reader :intentos

  def initialize
    reiniciar
  end

  def comprobar_numero(numero)
    return '¡Correcto!' if terminado?

    unless numero.is_a?(Integer) && numero.between?(NUMERO_MINIMO, NUMERO_MAXIMO)
      raise ArgumentError, 'El número debe estar entre 1 y 100.'
    end

    @intentos += 1

    if numero < @numero_secreto
      'Muy bajo'
    elsif numero > @numero_secreto
      'Muy alto'
    else
      @terminado = true
      '¡Correcto!'
    end
  end

  def reiniciar
    @numero_secreto = rand(NUMERO_MINIMO..NUMERO_MAXIMO)
    @intentos = 0
    @terminado = false
  end

  def terminado?
    @terminado
  end
end
