<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>

# Beamable Microservices
Beamable Microservices are Beamable's Cloud Code solution. It is a wrapper around a HTTP Server that makes the development process much simpler. These are written in C# and come with a set of development tools that are tightly integrated with the UE Editor and Beamable CLI.

This page explains the high-to-low-level concepts of Microservices and to what end they can be used. [Take a look here for a getting started guide](../guides/intro-microservices.md).

## Why this approach to Cloud-Code?
A lot of cloud-code solutions sacrifice a lot of flexibility, cost-efficiency, performance or developer experience in exchange for simplifying the simple case. Our goal was to focus on helping you with the complex cases while keeping the simple case easy to work.

We do so by this architecture:

![some_image](some_image.png)
// Realm A -> Microservice A or B
// Client Call Beamable Backend -> Forwards to Local or Realm Microservice via custom WebSocket protocol -> Responds back to client

The Microservice is:

- A wrapper around a WebSocket protocol and Job Scheduler with set of layered APIs you can use to easily write the simple cases and peel back to write the complex cases.
- Locally "debug-able" (really, just press Debug on Rider). [Collaboratively too](#collaborative-debugging).
- Deployed as a Docker container that you can customize.
- Promotable between Realms via the Portal OR our CLI (CI/CD folks rejoice).

It solves all these problems and the amount of code you actually need to write to expose an Endpoint your game can call is:
```csharp
[ClientCallable]  
public int Add(int a, int b)  
{  
    return a + b;  
}
```

The next three sections explain [Microservice Coding](#microservice-coding), [Common Developer Workflows](#common-developer-workflows), the [Microservice Window](#microservice-window) and [MicroStorages](#micro-storages). 

## Microservice Coding
Microservices inherit from the `Microservice` base class and are `partial` by default. Inside each Microservice class, you can annotate instance methods with the following attributes to various effects:

- `Callable`: This is the equivalent of a public endpoint. Any non-authenticated caller is allowed to invoke this function via a request.
- `ClientCallable`: This is equivalent to an authenticated request. Any authenticated user in the same realm as the microservice is able to run this.
- `AdminOnlyCallable`: These are similar to `ClientCallables` but requires the user to have admin privileges. They are useful for making utility endpoints called by internal developer tools.
- `ServerCallable`: This is equivalent to a trusted-server request. It requires authentication in the form of a Signed Request. Primarily, these are callable from your game's Dedicated Server builds.

Inside the method body, there are a few concepts that are relevant:

- `Context`: This field of the Microservice class has information about the request.
	- `Context.Cid` | `Context.Pid`: Contain the relevant realm information for the microservice.
	- `Context.UserId`: Contains the `GamerTag` for the account making the call. This is `0` for non-authenticated endpoints such as `Callables` and `ServerCallables`.
	- `Context.Body`: Contains the raw body (typically JSON) of the request, if any.
- `Services`: This field of the Microservice class gives you access to Beamable's Services from your microservice.
	- `Services.Inventory`: Access the inventory service...
	- `Services.Stats`: Access the stats service...
	- So on and so forth...

#### Constraints on Callable Functions
Our CLI is capable of generating Unreal bindings that will allow your Unreal code to call your microservice much like you would make an API call to Beamable. In order to generate these bindings, we have *some* restrictions on what types can and can't be on method signatures for `Callables`. The type-mapping seen in the [Content section](../features/content.md#supported-content-serialization) is what you can expect.

There are a few other limitations about these that you can find in our Standalone Microservice docs.

#### Making Requests on Behalf of Users
It is quite a common case that a Microservice needs to use one of our many APIs on behalf of a particular user. This allows you to re-use our APIs (that are usually written in a client-facing way) to be used for multiple users. A practical example:

> At the end of a MOBA match, you'll need to update player stats gathered during the match or process their account's new Experience or Rank. For this, you can make a `ServerCallable` called `ProcessMatchResults` and pass in information from your dedicated server whenever the match is over.

In order to make requests on behalf of users we provide the `AssumeNewUser` function. It gives you back a `UserRequestDataHandler` that has fields like `Context` and `Services`. Making API calls from this `assumedUser.Services.Stats` instance as opposed to the usual `this.Services` will make the request on behalf of the user.

#### Multiple Microservices and Organizing Code
The first impulse a lot of people have is to separate microservices semantically; one-per-feature. **We do not recommend this.** Here's why:

- Having a lot of microservices will increase your cost for *potentially* no benefit.
- Having a lot of microservices increases project complexity.
- Having a lot of microservices makes you add latency to things that otherwise wouldn't have it (cross microservice communication is possible, but rarely actually needed).
- Having a lot of microservices increases deployment times.

The key metric you should use to consider creating additional microservices is ***different load profiles at runtime***. Basically, if you have a set of features with similar expected load profiles, you can keep them together as the auto-scaling will work uniformly to handle the increased load. If you have services with spikey load profiles (either in memory usage or CPU), then consider putting each of them in their own service so that they can be scaled independently and faster than your other larger services.

> **Game Maker**: "If I have 5 features in one microservices, how do I organize my `____Callable` functions?"
>
> **Beamable**: "You can create new parts of the `partial` Microservice type. You can declare utility static functions as well and make most `____Callable` just forward the call along."

We've found these approaches gives you the proper runtime scalability for the lowest cost and provide a simple developer experience.

## Common Developer Workflows
There are a few different ways to work with Microservices in Unreal, each with their own advantages and disadvantages. So, here we make our recommendations about them.

These are NOT how-to guides, they are high-level descriptions to help you get a feel regarding how to work with Beamable and how its tools can be used to work alone and as a team.

#### Designing the API
If you're in the very early stages of solving a problem and you just want to get the features to work, there's a workflow that doesn't require you to open Unreal at all, allowing you to focus only on getting your `Callables` to work!

Here are the steps:

1. Write your `Callable`'s code in your IDE.
2. Press the Debug or Run button on the IDE.
3. Wait for the Service to Start.
	1. The service will print out `Service ready for traffic.`
4. The service prints out a Portal URL for you.
5. Access that.
6. From that page, you can make requests to your service as though your own developer account was a player in your realm.
7. Iterate quickly.

This allows you to get services that might have complex logic working first and integrating them into Unreal later. [Keep in mind the type restrictions on method signatures mentioned here](#constraints-on-callable-functions).

#### Integrating with Unreal
Whenever it becomes preferable or necessary (see [Federations](federation.md)) to test the microservice directly from Unreal's PIE mode, you can generate bindings for your `Callable` types and use them inside your game's code.

Here you have two options:

- Run the `dotnet beam project generate-client Path/to/Service/built/dll` command manually to generate these bindings.
	- This command regenerates your client bindings AND run Unreal's `Regenerate Project Files` utility for you.
- Add the line below to the `BeamableSettings` Property Group of your Microservice's `.csproj` file.
	- `<GenerateClientCode>true</GenerateClientCode>` 
	- This will run the above command automatically on every microservice rebuild (with changes).

We generate both C++ and Blueprint Bindings for every microservice `Callable`.

!!! info "IMPORTANT: Using the generated code in UE"
	The generated code exist inside a `__________MicroserviceClients` plugin. So, you should add this plugin as a dependency to any project/plugin you have from which you want to make calls to your microservices (don't forget to add it to `Target.cs` files as needed). Also, call `________MicroserviceClients.AddMicroserviceClients(this)` on any of the `Build.cs` files you have and want to communicate with a microservice.

Once you have these, you can:

1. Write code that uses the bindings to communicate with your service.
2. Recompile your UE editor (or Blueprint).
3. Run/Debug your local microservice (via the Microservice Window, IDE or `dotnet beam project run`).
4. Run PIE and hit the point where you call your microservice.
5. See your local service's `Callable`'s be hit.

If you are using [Federations](federation.md), there are a few particulars of this workflow of which you should be aware. If not, the above works as described.

#### Deploying to a Realm
Once you have things working locally, you'll likely want to make the Microservice available to other team members working on the realm. If you just push your code up, other team members would also have to run the service locally and that might not always be desirable.

As such, you should publish the services to the appropriate realm.

!!! info "Which realm?"
	How you wish to manage realms is a team-specific decision as there are cost implications per-microservice instance running in any realm to consider against how your team likes to work.
	
	 At Beamable's UE team, we prefer the "team members are responsible not to break other team members environment"-approach so we recommend that you test things thoroughly and then publish to your `dev` realm (where everybody is). 
	
	Another strategy might be to have a `designer-dev` that lives between `staging` and `dev` that should be more stable and then you push to `dev` first and eventually promote it to `designer-dev`. Again, this is for your lead and team to discuss and decide how you wish to work.
	
	Finally, you can also choose a `one realm per developer` approach though that introduces a lot of workflow overhead and makes [grug-brained developers](https://grugbrain.dev/) sad. Though, there are team-specific cases where that might be a valid approach.

The way to deploy services for our UE integration is 100% CLI-based. The documentation for it can be found here.

!!! info "Why no Deploy Editor UI?"
	If there's enough demand for it, we will consider adding it. However, deploying services is mostly done by engineers and CI/CD pipelines so we felt that compiling and opening the Editor just to do this didn't add enough value to the UE workflow.

#### Collaborative Debugging
This one is a banger. Imagine the following: 

- You have a service published in a realm with your designer working and testing against it.
- The designer does something that reveals a bug in your service.
- It is unclear what causes it exactly and but the designer can repro it consistently by playing in PIE.

Now, the usual flow for handling this situation would be similar to this:

- Make a ticket.
- Live with the bug while a ticket/task finds its way to an engineer, impacting designer productivity.
- Hope the engineer can repro it as consistently as the designer... or do it at all.
- Try to fix it in the future.

Or... you could instead use Beamable's Collaborative Debugging workflow:

- As the engineer, hop on a voice chat with the designer and make sure you're in the same realm as them.
- As the engineer, boot up your local service with a debugger attached and a breakpoint.
- As the designer, open the editor and the [Microservice Window's Collaboration](#microservice-window) tab for the service and select your engineer's email from the drop-down.
- As the designer, enter PIE and do what you do to repro the bug.
- As the engineer, observe your (conditional or data) breakpoint is hit.
- Quickly diagnose the issue and unblock the designer.


![image.png](microservice collaborative workflow.png)


Its really that simple. This is the closest cloud-code has ever gotten to Google-Drive-style collaboration around debugging.

## Microservice Window
This window is here to enable developers to start/stop local services, to read local service logs while in PIE and to configure local server settings for the collaborative workflow and for federations.

![image.png](microservice-window.png)

Tabs and filters
![image.png](microservice-selected-service.png)

Reading logs
![image.png](microservice-logs.png)


Federation tab forward to Federations concept
Collaboration tab forward to above section.

## Micro Storages
Beamable Microservices allow you to store data in Beamable's own managed services such as `Stats`(Per-Player key-value stores) and `Inventory` (Per-Player currency and item tracking). However, there are cases where you want to control your own data-model and indices. It might be necessary to hit your performance targets OR maybe it just makes your particular problem simpler to solve (instead of trying to fit it into our default stores).

For those cases, Beamable offers a `MicroStorage`. This is a wrapper around a database that you can write to from your microservices. At the moment, we only support `MongoDB`. Like Microservices, these are scoped by realm as well (as in, data from Realm A is only visible in Realm A). [You can find out more about here](docs link to SAMS Micro Storage!).

#### Local Development Implications
While you can develop microservices without Docker being run (except for its publishing step), you cannot do the same for `Microservices` that use `MicroStorages`. This is because the local running service expects there to be a locally running `MongoDB` instance it'll use as the Database.

To make sure the above is true, we run `MongoDB`'s official container in your local Docker instance. This is managed automatically on startup of the microservice BUT does introduce a dependency on docker for local iterative development.









