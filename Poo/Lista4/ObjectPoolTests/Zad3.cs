using System;
using System.Collections.Generic;
using NUnit.Framework;

public class Reusable
{
    public void DoWork()
    {
        Console.WriteLine("Doing work...");
    }
}

public class ObjectPool
{
    private int _poolSize;
    private List<Reusable> _pool = new List<Reusable>();
    private List<Reusable> _acquired = new List<Reusable>();

    public ObjectPool(int poolSize)
    {
        if (poolSize <= 0)
        {
            throw new ArgumentException("Pool size must be greater than 0.");
        }
        this._poolSize = poolSize;
    }

    public Reusable AcqureReusable()
    {
        if (_acquired.Count == _poolSize)
        {
            throw new ArgumentException("No available objects in the pool.");
        }
        if (_pool.Count == 0)
        {
            var reusable = new Reusable();
            _pool.Add(reusable);
        }
        var element = _pool[0];
        _pool.Remove(element);
        _acquired.Add(element);
        return element;
    }

    public void ReleaseReusable(Reusable reusable)
    {
        if (!_acquired.Contains(reusable))
        {
            throw new ArgumentException("This object does not belong to the pool.");
        }
        _acquired.Remove(reusable);
        _pool.Add(reusable);
    }
}

public class BetterReusable
{
    private static ObjectPool _pool = new ObjectPool(5);
    private Reusable _reusable;
    private bool _isReleased = false;

    public BetterReusable()
    {
        _reusable = _pool.AcqureReusable();
    }

    public void DoWork()
    {
        if (_isReleased)
        {
            throw new InvalidOperationException("Object has been released and cannot be used.");
        }
        _reusable.DoWork();
    }

    public void Release()
    {
        if (_isReleased)
        {
            throw new InvalidOperationException("Object has already been released.");
        }
        _pool.ReleaseReusable(_reusable);
        _isReleased = true;
    }
}


[TestFixture]
public class ObjectPoolTests
{
    [Test]
    public void InvalidSize()
    {
        Assert.Throws<ArgumentException>(() => new ObjectPool(0));
    }

    [Test]
    public void ValidSize()
    {
        var reusable = new BetterReusable();
        if (reusable == null)
        {
            Assert.Fail("Object is null");
        }
    }

    [Test]
    public void ReusedInstance()
    {
        var reusable = new BetterReusable();
        reusable.Release();
        var reusable2 = new BetterReusable();
        if (reusable2 == null)
        {
            Assert.Fail("Object is null");
        }
    }

    [Test]
    public void ReleaseInvalidInstance()
    {
        var pool = new ObjectPool(1);
        var reusable = new Reusable();
        Assert.Throws<ArgumentException>(() => pool.ReleaseReusable(reusable));
    }

    [Test]
    public void DoWorkAfterReleaseThrowsException()
    {
        var reusable = new BetterReusable();
        reusable.Release();
        Assert.Throws<InvalidOperationException>(() => reusable.DoWork());
    }
}