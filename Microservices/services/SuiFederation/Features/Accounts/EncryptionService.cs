using System;
using System.IO;
using System.Security.Cryptography;

namespace Beamable.SuiFederation.Features.Accounts;

public static class EncryptionService
{
    private const int KeySize = 32; // 256-bit key
    private const int IvSize = 16; // AES block size
    private const int Iterations = 20000; // PBKDF2 iterations

    public static string Encrypt(string plainText, string password)
    {
        var salt = GenerateRandomBytes(16);
        var key = DeriveKey(password, salt);

        using var aes = Aes.Create();
        aes.Key = key;
        aes.GenerateIV();

        using var encryptor = aes.CreateEncryptor(aes.Key, aes.IV);
        using var ms = new MemoryStream();

        ms.Write(salt, 0, salt.Length);
        ms.Write(aes.IV, 0, aes.IV.Length);

        using (var cs = new CryptoStream(ms, encryptor, CryptoStreamMode.Write))
        using (var sw = new StreamWriter(cs))
        {
            sw.Write(plainText);
        }

        return Convert.ToBase64String(ms.ToArray());
    }

    public static string Decrypt(string cipherText, string password)
    {
        var cipherBytes = Convert.FromBase64String(cipherText);

        var salt = new byte[16];
        var iv = new byte[IvSize];

        Array.Copy(cipherBytes, 0, salt, 0, salt.Length);
        Array.Copy(cipherBytes, salt.Length, iv, 0, iv.Length);

        var key = DeriveKey(password, salt);

        using var aes = Aes.Create();
        aes.Key = key;
        aes.IV = iv;

        var actualCipherText = new byte[cipherBytes.Length - salt.Length - iv.Length];
        Array.Copy(cipherBytes, salt.Length + iv.Length, actualCipherText, 0, actualCipherText.Length);

        using var decryptor = aes.CreateDecryptor(aes.Key, aes.IV);
        using var ms = new MemoryStream(actualCipherText);
        using var cs = new CryptoStream(ms, decryptor, CryptoStreamMode.Read);
        using var sr = new StreamReader(cs);

        return sr.ReadToEnd();
    }

    private static byte[] GenerateRandomBytes(int size)
    {
        using var rng = RandomNumberGenerator.Create();
        var bytes = new byte[size];
        rng.GetBytes(bytes);
        return bytes;
    }

    private static byte[] DeriveKey(string password, byte[] salt)
    {
        using var pbkdf2 = new Rfc2898DeriveBytes(password, salt, Iterations, HashAlgorithmName.SHA256);
        return pbkdf2.GetBytes(KeySize);
    }
}