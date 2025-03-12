using System.IO;
using System.Threading.Tasks;

namespace Beamable.SuiFederation.Features.Contract.Handlers;

public static class ContractWriter
{
    public static async Task WriteContract(string path, string contract)
    {
        var directory = Path.GetDirectoryName(path);
        if (!string.IsNullOrWhiteSpace(directory))
        {
            Directory.CreateDirectory(directory);
        }
        await File.WriteAllTextAsync(path,contract);
    }
}