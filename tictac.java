import java.util.Scanner;

public class TicTacToe {
    static char[] square = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
    static String player1, player2 = "BOT";
    static boolean playWithBot = false;

    public static void displayBoard() {
        System.out.println();
        for (int i = 0; i < 9; i++) {
            System.out.print(" " + square[i] + " ");
            if (i % 3 != 2)
                System.out.print("|");
            if (i % 3 == 2 && i != 8)
                System.out.println("\n-----------");
        }
        System.out.println("\n");
    }

    public static int checkWin() {
        int[][] winCombos = {
                { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 },
                { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 },
                { 0, 4, 8 }, { 2, 4, 6 }
        };

        for (int[] combo : winCombos) {
            int a = combo[0], b = combo[1], c = combo[2];
            if (square[a] == square[b] && square[b] == square[c]) {
                return (square[a] == 'X') ? 1 : 2;
            }
        }
        return 0;
    }

    public static boolean markBox(int player, int box) {
        if (box < 0 || box > 8 || square[box] == 'X' || square[box] == 'O') {
            System.out.println("Invalid move! Try again.");
            return false;
        }
        square[box] = (player == 1) ? 'X' : 'O';
        return true;
    }

    public static boolean isDraw() {
        for (char c : square) {
            if (c != 'X' && c != 'O')
                return false;
        }
        return true;
    }

    public static int getBotMove() {
        for (int i = 0; i < 9; i++) {
            if (square[i] != 'X' && square[i] != 'O')
                return i;
        }
        return -1;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int mode;

        System.out.println("===== TIC TAC TOE =====");
        System.out.println("1. Play with Friend");
        System.out.println("2. Play with BOT");
        System.out.print("Choose mode (1 or 2): ");
        mode = scanner.nextInt();
        scanner.nextLine(); // consume newline

        if (mode == 1) {
            playWithBot = false;
            System.out.print("Enter Player 1 Name (X): ");
            player1 = scanner.nextLine();
            System.out.print("Enter Player 2 Name (O): ");
            player2 = scanner.nextLine();
        } else {
            playWithBot = true;
            System.out.print("Enter Your Name (X): ");
            player1 = scanner.nextLine();
            System.out.println("You will play against the BOT (O)");
        }

        int currentPlayer = 1, box, result = 0;

        while (true) {
            displayBoard();

            if (currentPlayer == 1 || !playWithBot) {
                String currentName = (currentPlayer == 1) ? player1 : player2;
                System.out.print(currentName + ", enter your move (0-8): ");
                box = scanner.nextInt();
                if (!markBox(currentPlayer, box))
                    continue;
            } else {
                System.out.println("BOT is thinking...");
                box = getBotMove();
                markBox(currentPlayer, box);
                System.out.println("BOT chose box " + box);
            }

            result = checkWin();
            if (result == 1 || result == 2) {
                displayBoard();
                String winner = (result == 1) ? player1 : player2;
                System.out.println("🎉 Congratulations " + winner + "! You have won the game! 🎉");
                break;
            }

            if (isDraw()) {
                displayBoard();
                System.out.println("It's a draw! Well played " + player1 + " and " + player2 + ".");
                break;
            }

            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }

        scanner.close();
    }
}
