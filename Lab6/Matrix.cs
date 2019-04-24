using System;
using System.Text;

namespace Lab6 {
    class Matrix : ICloneable {
        private double[,] arr;
        private int row;
        private int col;
        private static int count;
        private int ID;

        public Matrix() : this(0, 0) {

        }

        ~Matrix() {
            arr = null;
        }

        public Matrix(int row, int col) : this(row, col, (double[,])null) {

        }

        public Matrix(int row, int col, double[,] arr) {
            count++;
            ID = count;
            if (row * col == 0) {
                this.row = 0;
                this.col = 0;
                this.arr = null;
            }
            else {
                this.row = row;
                this.col = col;
                this.arr = new double[this.row, this.col];
                for (int i = 0; i < this.row; i++) {
                    for (int j = 0; j < this.col; j++) {
                        this.arr[i, j] = arr != null ? arr[i, j] : 0.0;
                    }
                }
            }
        }

        public Matrix(int row_col, double[,] arr) : this(row_col, row_col, arr) {

        }

        public Matrix(int row, int col, params double[] num) : this(row, col) {
            int k = 0;
            for (int i = 0; i < this.row; i++) {
                for (int j = 0; j < this.col; j++) {
                    if (k == num.Length) return;
                    arr[i, j] = num[k];
                    k++;
                }
            }
        }

        public Matrix(int row_col, params double[] num) : this(row_col, row_col, num) {

        }

        public Matrix(int row, int col, Func<int, int, double> func) : this(row, col) {
            for (int i = 0; i < this.row; i++) {
                for (int j = 0; j < this.col; j++) {
                    arr[i, j] = func(i, j);
                }
            }
        }

        public Matrix(int row_col, Func<int, int, double> func) : this(row_col, row_col, func) {

        }

        public Matrix(Matrix m) : this(m.row, m.col, m.arr) {

        }

        public static bool CheckSumOrSub(Matrix m1, Matrix m2) {
            return m1.col == m2.col && m1.row == m2.row;
        }

        public static bool CheckMul(Matrix m1, Matrix m2) {
            return m1.col == m2.row;
        }

        public int Row {
            get {
                return row;
            }
        }

        public int Col {
            get {
                return col;
            }
        }

        public static int Count {
            get {
                return count;
            }
        }

        public int getID {
            get {
                return ID;
            }
        }

        public double this[int i, int j] {
            get {
                if ((i < 0 || i >= row) && (j < 0 || j >= col)) throw new ArgumentOutOfRangeException("Выход за границы массива в объекте №" + Convert.ToString(ID));
                return arr[i, j];
            }
            set {
                if ((i < 0 || i >= row) && (j < 0 || j >= col)) throw new ArgumentOutOfRangeException("Выход за границы массива в объекте №" + Convert.ToString(ID));
                arr[i, j] = value;
            }
        }

        public double Max() {
            if (arr == null) throw new ArgumentNullException("Невозможно выполнить действие в нулевом объекте №" + Convert.ToString(ID));
            double max = arr[0, 0];

            for (int i = 0; i < col; i++) {
                for (int j = 0; j < row; j++) {
                    if (arr[i, j] > max) max = arr[i, j];
                }
            }

            return max;
        }

        public double Min() {
            if (arr == null) throw new ArgumentNullException("Невозможно выполнить действие в нулевом объекте №" + Convert.ToString(ID));
            double min = arr[0, 0];

            for (int i = 0; i < col; i++) {
                for (int j = 0; j < row; j++) {
                    if (arr[i, j] < min) min = arr[i, j];
                }
            }

            return min;
        }

        public override string ToString() {
            var str = new StringBuilder();

            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    str.Append($"{arr[i, j]}  ");
                }
                str.AppendLine();
            }

            return str.ToString();
        }

        public object Clone() {
            return new Matrix(this);
        }

        public static Matrix operator +(Matrix m1, Matrix m2) {
            if (!CheckSumOrSub(m1, m2)) throw new InvalidOperationException("Объекты №" + Convert.ToString(m1.ID) + " и №"+ Convert.ToString(m2.ID) + ": Сложение невозможно!");
            Matrix temp = new Matrix(m1);

            for (int i = 0; i < temp.row; i++) {
                for (int j = 0; j < temp.col; j++) {
                    temp.arr[i, j] += m2.arr[i, j];
                }
            }

            return temp;
        }

        public static Matrix operator -(Matrix m1, Matrix m2) {
            if (!CheckSumOrSub(m1, m2)) throw new InvalidOperationException("Объекты №" + Convert.ToString(m1.ID) + " и №" + Convert.ToString(m2.ID) + ": Вычитание невозможно!");
            Matrix temp = new Matrix(m1.row, m1.col);

            for (int i = 0; i < temp.row; i++) {
                for (int j = 0; j < temp.col; j++) {
                    temp.arr[i, j] = m1.arr[i, j] - m2.arr[i, j];
                }
            }

            return temp;
        }

        public static Matrix operator *(Matrix m1, Matrix m2) {
            if (!CheckMul(m1, m2)) throw new InvalidOperationException("Объекты №" + Convert.ToString(m1.ID) + " и №" + Convert.ToString(m2.ID) + ": Умножение невозможно!");
            Matrix temp = new Matrix(m1.row, m2.col);

            for (int i = 0; i < temp.row; i++) {
                for (int j = 0; j < temp.col; j++) {
                    for (int k = 0; k < m1.col; k++) {
                        temp.arr[i, j] += m1.arr[i, k] * m2.arr[k, j];
                    }
                }
            }

            return temp;
        }

        public static Matrix operator *(Matrix m1, double k) {
            Matrix temp = new Matrix(m1.row, m1.col);

            for (int i = 0; i < temp.row; i++) {
                for (int j = 0; j < temp.col; j++) {
                    temp.arr[i, j] *= k;
                }
            }

            return temp;
        }

        public static Matrix operator *(double k, Matrix m1) {
            return m1 * k;
        }
    }
}
