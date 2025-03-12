using System.Threading.Tasks;
using Beamable.Common.Content;

namespace Beamable.SuiFederation.Features.Contract.Handlers;

public interface IContentContractHandler
{
    Task HandleContract(IContentObject clientContentInfo);
}