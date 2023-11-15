using Beamable.Server;

namespace Beamable.MSPlayground;

[Microservice("MSPlayground")]
public class MSPlayground : Microservice
{
	[ClientCallable]
	public int Add(int a, int b)
	{
		return a + b;
	}
}