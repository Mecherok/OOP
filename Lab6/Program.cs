using System;
//IEnumerable,enumerator clone явный, выделение памяти в конструкторе, умножение исправить, проверка на null в конструкторе с arr, row и col можно не хранить, строки  
// в исключениях исправить с помощью string.format

namespace Lab6 {
    class Program {
        public delegate double Func(int i, int j);
        static Random rnd = new Random();
        static void Main(string[] args) {
            try {
                Func<int, int, double> func;
                func = Rand;
                double[,] arr = { { 1.543444, 2.0111123 } , { 3.445550, 4.44440 } };
                Matrix m4= new Matrix(3, 3);
                Matrix m = new Matrix(arr);
                Matrix m1 = new Matrix(arr);
                Matrix m2 = new Matrix(2, 2, 1.0, 2.0, 3.0, 4.0);
                Matrix m3 = new Matrix(2, 1.0, 2.0, 3.0, 50.0);
                Matrix mm = new Matrix();
                Console.WriteLine("{0:F3:10}", m1);
                Console.WriteLine(m2);
                Console.WriteLine(m3);
            }
            catch (Exception ex) {
                Console.WriteLine(ex.Message);
            }
        }
        private static double Rand(int i, int j) {
            return rnd.Next(0, 10);
        }
    }
}
