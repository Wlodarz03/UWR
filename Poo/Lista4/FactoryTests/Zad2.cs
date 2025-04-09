using System;
using System.Collections.Generic;

// Interfejs dla figur
public interface IShape
{
    int GetArea();
}

// Implementacje różnych figur
public class Square : IShape
{
    private int size;
    public Square(int size) => this.size = size;

    public int GetArea() => size * size;
}

public class Rectangle : IShape
{
    private int width, height;
    public Rectangle(int width, int height)
    {
        this.width = width;
        this.height = height;
    }

    public int GetArea() => width * height;
}

// Interfejs fabryki pomocniczej
public interface IShapeFactoryWorker
{
    string ShapeName { get; }
    IShape Create(params object[] parameters);
}

// Implementacje fabryk pomocniczych
public class SquareFactoryWorker : IShapeFactoryWorker
{
    public string ShapeName => "Square";

    public IShape Create(params object[] parameters)
    {
        if (parameters.Length == 1 && parameters[0] is int size)
            return new Square(size);
        throw new ArgumentException("Invalid parameters for Square.");
    }
}

public class RectangleFactoryWorker : IShapeFactoryWorker
{
    public string ShapeName => "Rectangle";

    public IShape Create(params object[] parameters)
    {
        if (parameters.Length == 2 && parameters[0] is int width && parameters[1] is int height)
            return new Rectangle(width, height);
        throw new ArgumentException("Invalid parameters for Rectangle.");
    }
}

// Główna klasa ShapeFactory
public class ShapeFactory
{
    private Dictionary<string, IShapeFactoryWorker> workers = new Dictionary<string, IShapeFactoryWorker>();

    public ShapeFactory()
    {
        RegisterWorker(new SquareFactoryWorker());
    }

    public void RegisterWorker(IShapeFactoryWorker worker)
    {
        workers[worker.ShapeName] = worker;
    }

    public IShape CreateShape(string shapeName, params object[] parameters)
    {
        if (workers.TryGetValue(shapeName, out var worker))
        {
            return worker.Create(parameters);
        }
        throw new InvalidOperationException($"Shape '{shapeName}' not registered.");
    }
}

namespace ShapesFactory.Tests
{
    [TestFixture]
    public class ShapeFactoryTests
    {
        [Test]
        public void AddSingleSquare()
        {
            ShapeFactory factory = new ShapeFactory();
            IShape square = factory.CreateShape("Square", 4);
            Assert.That(square.GetArea(), Is.EqualTo(16));
            
        }

        [Test]
        public void CallWithInvalidArgument()
        {
            ShapeFactory factory = new ShapeFactory();
            Assert.Throws<ArgumentException>(() => factory.CreateShape("Square", "wrong_argument"));
        }

        [Test]
        public void CallWithoutRectangleFactoryWorker()
        {
            ShapeFactory factory = new ShapeFactory();
            Assert.Throws<InvalidOperationException>(() => factory.CreateShape("Rectangle", 4, 5));
        }
        [Test]
        public void CallWithNewWorker()
        {
            ShapeFactory factory = new ShapeFactory();
            factory.RegisterWorker(new RectangleFactoryWorker());

            IShape square = factory.CreateShape("Rectangle", 7, 10);

            if (square == null){
                Assert.Fail("Rectangle is null");
            }
            else{
                Assert.That(square.GetArea(), Is.EqualTo(70));
            }

        }
    }
}