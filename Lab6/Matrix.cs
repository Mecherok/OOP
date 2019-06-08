using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;

namespace Lab6 {
    class Matrix : ICloneable, IFormattable, IEquatable<Matrix>, IEnumerable<double> {
        private double[,] arr;
        private static int count;
        private int id;

        public Matrix() : this(0, 0) {
             
        }

        ~Matrix() {
            arr = null;
        }

        public Matrix(int row, int col) {
            count++;
            id = count;
            if (row < 0 || col < 0) throw new ArgumentException(String.Format($"Неверный размер матрицы №{id}!"));
            arr = new double[row, col];
        }

        public Matrix(int row_col) : this(row_col, row_col) {

        }

        public Matrix(double[,] arr) : this(arr == null ? throw new ArgumentNullException("Ссылка на объект не указывает на экземпляр объекта") 
            : arr.GetLength(0), arr.GetLength(1)) {
            for (int i = 0; i < arr.GetLength(0); i++) {
                for (int j = 0; j < arr.GetLength(1); j++) {
                    this.arr[i, j] = arr[i, j];
                }
            }
        }

        public Matrix(int row, int col, params double[] num) : this(row, col) {
            int k = 0;
            for (int i = 0; i < arr.GetLength(0); i++) {
                for (int j = 0; j < arr.GetLength(1); j++) {
                    if (k == num.Length) return;
                    arr[i, j] = num[k];
                    ++k;
                }
            }
        }

        public Matrix(int row_col, params double[] num) : this(row_col, row_col, num) {

        }

        public Matrix(int row, int col, Func<int, int, double> func) : this(row, col) {
            for (int i = 0; i < arr.GetLength(0); i++) {
                for (int j = 0; j < arr.GetLength(1); j++) {
                    arr[i, j] = func(i, j);
                }
            }
        }

        public Matrix(int row_col, Func<int, int, double> func) : this(row_col, row_col, func) {

        }

        public Matrix(Matrix m) : this(m?.arr) {

        }

        public static bool CheckSumOrSub(Matrix m1, Matrix m2) {
            return m1.arr.GetLength(0) == m2.arr.GetLength(0) && m2.arr.GetLength(1) == m2.arr.GetLength(1);
        }

        public static bool CheckMul(Matrix m1, Matrix m2) {
            return m1.arr.GetLength(1) == m2.arr.GetLength(0);
        }

        public int Row {
            get {
                return arr.GetLength(0);
            }
        }

        public int Col {
            get {
                return arr.GetLength(1);
            }
        }

        public static int Count {
            get {
                return count;
            }
        }

        public int ID {
            get {
                return id;
            }
        }

        public double this[int i, int j] {
            get {
                if ((i < 0 || i >= arr.GetLength(0)) && (j < 0 || j >= arr.GetLength(1))) throw
                    new IndexOutOfRangeException(String.Format($"Выход за границы массива в объекте №{id}!"));
                return arr[i, j];
            }
            set {
                if ((i < 0 || i >= arr.GetLength(0)) && (j < 0 || j >= arr.GetLength(1))) throw
                    new IndexOutOfRangeException(String.Format($"Выход за границы массива в объекте №{id}!"));
                arr[i, j] = value;
            }
        }

        object ICloneable.Clone() {
            return Clone();
        }

        public Matrix Clone() {
            return new Matrix(this);
        }

        public override string ToString() {
            return ToString(null, null);
        }

        public string ToString(string format, IFormatProvider formatProvider) {
            format = format ?? "G";
            formatProvider = formatProvider ?? System.Globalization.CultureInfo.CurrentCulture;

            var splitted = format.Split(':');
            var numberFormat = splitted[0];
            int width = splitted.Length > 1 ? int.Parse(splitted[1]) : 0;

            var resultFormat = splitted.Length > 1 ? $"{{0,{width}:{numberFormat}}}" : $"{{0:{numberFormat}}} ";

            var str = new StringBuilder();

            for (int i = 0; i < arr.GetLength(0); i++) {
                for (int j = 0; j < arr.GetLength(1); j++) {
                    str.AppendFormat(formatProvider, resultFormat, arr[i, j]);
                }
                str.AppendLine();
            }

            return str.ToString();
        }

        public bool Equals(Matrix other) {
            if (arr.GetLength(0) != other.arr.GetLength(0) || arr.GetLength(1) != other.arr.GetLength(1)) {
                return false;
            }
            else {
                for (int i = 0; i < arr.GetLength(0); i++) {
                    for (int j = 0; j < arr.GetLength(1); j++) {
                        if (arr[i, j] != other.arr[i, j]) return false;
                    }
                }
            }
            return true;
        }

        public IEnumerator<double> GetEnumerator() {
            for (int i = 0; i < arr.GetLength(0); i++) {
                for (int j = 0; j < arr.GetLength(1); j++) {
                    yield return arr[i, j];
                }
            }
        }

        IEnumerator IEnumerable.GetEnumerator() {
            return GetEnumerator();
        }

        public static Matrix operator +(Matrix m1, Matrix m2) {
            if (!CheckSumOrSub(m1, m2)) throw new InvalidOperationException(String.Format($"Объекты №{m1.id} и №{m2.id} : Сложение невозможно!"));
            Matrix temp = new Matrix(m1);

            for (int i = 0; i < temp.arr.GetLength(0); i++) {
                for (int j = 0; j < temp.arr.GetLength(1); j++) {
                    temp.arr[i, j] += m2.arr[i, j];
                }
            }

            return temp;
        }

        public static Matrix operator -(Matrix m1, Matrix m2) {
            if (!CheckSumOrSub(m1, m2)) throw new InvalidOperationException(String.Format($"Объекты №{m1.id} и №{m2.id} : Вычитание невозможно!"));
            Matrix temp = new Matrix(m1);
              
            for (int i = 0; i < temp.arr.GetLength(0); i++) {
                for (int j = 0; j < temp.arr.GetLength(1); j++) {
                    temp.arr[i, j] -= m2.arr[i, j];
                }
            }

            return temp;
        }

        public static Matrix operator *(Matrix m1, Matrix m2) {
            if (!CheckMul(m1, m2)) throw new InvalidOperationException(String.Format($"Объекты №{m1.id} и №{m2.id} : Умножение невозможно!"));
            Matrix temp = new Matrix(m1.arr.GetLength(0), m2.arr.GetLength(1));

            for (int i = 0; i < temp.arr.GetLength(0); i++) {
                for (int j = 0; j < temp.arr.GetLength(1); j++) {
                    for (int k = 0; k < m1.arr.GetLength(1); k++) {
                        temp.arr[i, j] += m1.arr[i, k] * m2.arr[k, j];
                    }
                }
            }

            return temp;
        }

        public static Matrix operator *(Matrix m1, double k) {
            Matrix temp = new Matrix(m1);

            for (int i = 0; i < temp.arr.GetLength(0); i++) {
                for (int j = 0; j < temp.arr.GetLength(1); j++) {
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
