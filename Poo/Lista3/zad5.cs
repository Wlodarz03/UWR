
public interface IUserStore<TUser> : IDisposable where TUser : class
{
    Task<string> GetUserIdAsync(TUser user, CancellationToken cancellationToken);
    Task<string> GetUserNameAsync(TUser user, CancellationToken cancellationToken);
    Task SetUserNameAsync(TUser user, string userName, CancellationToken cancellationToken);
    Task<string> GetNormalizedUserNameAsync(TUser user, CancellationToken cancellationToken);
    Task SetNormalizedUserNameAsync(TUser user, string normalizedName, CancellationToken cancellationToken);
    Task<IdentityResult> CreateAsync(TUser user, CancellationToken cancellationToken);
    Task<IdentityResult> UpdateAsync(TUser user, CancellationToken cancellationToken);
    Task<IdentityResult> DeleteAsync(TUser user, CancellationToken cancellationToken);
    Task<TUser> FindByIdAsync(string userId, CancellationToken cancellationToken);
    Task<TUser> FindByNameAsync(string normalizedUserName, CancellationToken cancellationToken);
}

//Interfejs do odczytu danych użytkownika:
public interface IUserQueryStore<TUser> where TUser : class
{
    Task<TUser> FindByIdAsync(string userId, CancellationToken cancellationToken);
    Task<TUser> FindByNameAsync(string normalizedUserName, CancellationToken cancellationToken);
    Task<string> GetUserIdAsync(TUser user, CancellationToken cancellationToken);
    Task<string> GetUserNameAsync(TUser user, CancellationToken cancellationToken);
    Task<string> GetNormalizedUserNameAsync(TUser user, CancellationToken cancellationToken);
}

//Interfejs do zapisu danych użytkownika:
public interface IUserCommandStore<TUser> where TUser : class
{
    Task SetUserNameAsync(TUser user, string userName, CancellationToken cancellationToken);
    Task SetNormalizedUserNameAsync(TUser user, string normalizedName, CancellationToken cancellationToken);
    Task<IdentityResult> CreateAsync(TUser user, CancellationToken cancellationToken);
    Task<IdentityResult> UpdateAsync(TUser user, CancellationToken cancellationToken);
    Task<IdentityResult> DeleteAsync(TUser user, CancellationToken cancellationToken);
}