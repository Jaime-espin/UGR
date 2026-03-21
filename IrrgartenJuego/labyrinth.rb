require_relative 'monster'
require_relative 'player'
require_relative 'shield'
require_relative 'weapon'

module Irrgarten
  class Labyrinth
    BLOCK_CHAR = 'X'
    EMPTY_CHAR = '-'
    MONSTER_CHAR = 'M'
    COMBAT_CHAR = 'C'
    EXIT_CHAR = 'E'
    ROW = 0
    COL = 1

    def initialize(nRows, nCols, exitRow, exitCol)
      @n_rows = nRows.to_i
      @n_cols = nCols.to_i
      @exit_col = exitCol.to_i
      @exit_row = exitRow.to_i

      @monsters = Array.new(@n_rows) { Array.new(@n_cols, nil) }
      @players = Array.new(@n_rows) { Array.new(@n_cols, nil) }
      @labyrinth = Array.new(@n_rows) { Array.new(@n_cols, EMPTY_CHAR) }

      @labyrinth[@exit_row][@exit_col] = EXIT_CHAR
    end

    def have_a_winner
      !@players[@exit_row][@exit_col].nil?
    end

    def to_s
      s = ''
      s += "LABYRINTH (Dimensions: #{@n_rows} X #{@n_cols})\n"
      @n_rows.times do |i|
        @n_cols.times { s += '--' }
        s += "\n|"
        @n_cols.times do |j|
          s += "#{@labyrinth[i][j]}|"
        end
        s += "\n"
      end
      s
    end

    def add_monster(row, col, monster)
      return unless pos_ok(row, col)

      @labyrinth[row][col] = MONSTER_CHAR
      monster.set_pos(row, col)
      @monsters[row][col] = monster
    end

    def spread_players(players)
      players.each do |player|
        p = player
        pos = random_empty_pos
        put_player_2d(-1, -1, pos[ROW], pos[COL], p)
      end
    end

    def put_player(direction, player)
      old_row = player.row
      old_col = player.col

      new_pos = dir2_pos(old_row, old_col, direction)
      put_player_2d(old_row, old_col, new_pos[ROW], new_pos[COL], player)
    end

    def add_block(orientation, start_row, start_col, length)
      if orientation == Orientation::VERTICAL
        inc_row = 1
        inc_col = 0
      else
        inc_row = 0
        inc_col = 1
      end
      row = start_row
      col = start_col

      while pos_ok(row, col) && empty_pos(row, col) && length > 0
        @labyrinth[row][col] = BLOCK_CHAR
        length -= 1
        row += inc_row
        col += inc_col
      end
    end

    def valid_moves(row, col)
      output = []
      output << Directions::DOWN if can_step_on(row + 1, col)

      output << Directions::UP if can_step_on(row - 1, col)

      output << Directions::RIGHT if can_step_on(row, col + 1)

      output << Directions::LEFT if can_step_on(row, col - 1)

      output
    end

    private

    def pos_ok(row, col)
      row < @n_rows && col < @n_cols && row >= 0 && col >= 0
    end

    def empty_pos(row, col)
      @labyrinth[row][col] == EMPTY_CHAR
    end

    def monster_pos(row, col)
      @labyrinth[row][col] == MONSTER_CHAR
    end

    def exit_pos(row, col)
      row == @exit_row && col == @exit_col
    end

    def combat_pos(row, col)
      @labyrinth[row][col] == COMBAT_CHAR
    end

    def can_step_on(row, col)
      pos_ok(row, col) && (empty_pos(row, col) || monster_pos(row, col)) || exit_pos(row, col)
    end

    def update_old_pos(row, col)
      return unless pos_ok(row, col)

      @labyrinth[row][col] = if combat_pos(row, col)
                               MONSTER_CHAR
                             else
                               EMPTY_CHAR
                             end
    end

    def dir2_pos(row, col, direction)
      return [row, col] if direction.nil?

      case direction
      when Directions::DOWN
        row += 1
      when Directions::LEFT
        col -= 1
      when Directions::RIGHT
        col += 1
      when Directions::UP
        row -= 1
      end
      [row, col]
    end

    def random_empty_pos
      row = 0
      col = 0
      loop do
        if Dice.respond_to?(:random_pos)
          row = Dice.random_pos(@n_rows)
          col = Dice.random_pos(@n_cols)
        else
          row = Dice.randomPos(@n_rows)
          col = Dice.randomPos(@n_cols)
        end
        break if empty_pos(row, col)
      end

      [row, col]
    end

    def put_player_2d(old_row, old_col, row, col, player)
      output = nil
      if can_step_on(row, col)
        if pos_ok(row, col)
          p = @players[old_row][old_col]
          if p == player
            update_old_pos(old_row, old_col)
            @players[old_row][old_col] = nil
          end
        end
        monster_pos = monster_pos(row, col)
        if monster_pos
          @labyrinth[row][col] = COMBAT_CHAR
          output = @monsters[row][col]
        else
          number = player.number
          @labyrinth[row][col] = number
        end
        @players[row][col] = player
        player.set_pos(row, col)
      end
      output
    end
  end
end
