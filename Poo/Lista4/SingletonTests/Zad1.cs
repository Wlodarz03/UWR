using System;
using System.Threading;
using System.Threading.Tasks;
using NUnit.Framework;

// Singleton dla całego procesu
public sealed class SingletonProcess
{
    private static readonly SingletonProcess instance = new SingletonProcess();
    private SingletonProcess() {}
    public static SingletonProcess Instance => instance;
}

// Singleton dla każdego wątku
public sealed class SingletonThread
{
    private static readonly ThreadLocal<SingletonThread> instance = new ThreadLocal<SingletonThread>(() => new SingletonThread());
    private SingletonThread() {}
    public static SingletonThread Instance => instance.Value;
}

// Singleton z czasem życia 5 sekund
public sealed class SingletonTimed
{
    private static SingletonTimed instance;
    private static long timestamp;
    private static readonly object lockObj = new object();

    private SingletonTimed() {}

    public static SingletonTimed Instance
    {
        get
        {
            lock (lockObj)
            {
                long currentTime = DateTimeOffset.UtcNow.ToUnixTimeMilliseconds();
                if (instance == null || (currentTime - timestamp) > 5000)
                {
                    instance = new SingletonTimed();
                    timestamp = currentTime;
                }
                return instance;
            }
        }
    }
}

// Testy jednostkowe
namespace Singleton.Tests
{
    [TestFixture]
    public class Tests
    {
        [Test]
        public void TestSingletonProcess()
        {
            var a = SingletonProcess.Instance;
            var b = SingletonProcess.Instance;
            Assert.That(a, Is.SameAs(b)); 
        }

        [Test]
        public void TestSingletonThread()
        {
            SingletonThread instance1 = null;
            SingletonThread instance2 = null;

            var task1 = Task.Run(() => instance1 = SingletonThread.Instance);
            var task2 = Task.Run(() => instance2 = SingletonThread.Instance);

            Task.WaitAll(task1, task2);
            Assert.That(instance1, Is.Not.SameAs(instance2)); 
        }

        [Test]
        public void TestSingletonTimed()
        {
            var a = SingletonTimed.Instance;
            Thread.Sleep(3000);
            var b = SingletonTimed.Instance;
            Assert.That(a, Is.SameAs(b)); 

            Thread.Sleep(6000);
            var c = SingletonTimed.Instance;
            Assert.That(a, Is.Not.SameAs(c)); 
        }
    }
}
