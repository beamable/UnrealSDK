
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/CreateRoomRequestBody.h"
#include "AutoGen/CreateRoomResponse.h"

#include "PostRoomsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostRoomsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UCreateRoomRequestBody* Body;

	// Beam Base Request Declaration
	UPostRoomsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostRoomsRequest* MakePostRoomsRequest(int64 _ObjectId, FString _RoomName, bool _bKeepSubscribed, TArray<int64> _Players, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRoomsSuccess, FBeamRequestContext, Context, UPostRoomsRequest*, Request, UCreateRoomResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRoomsError, FBeamRequestContext, Context, UPostRoomsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostRoomsComplete, FBeamRequestContext, Context, UPostRoomsRequest*, Request);

using FPostRoomsFullResponse = FBeamFullResponse<UPostRoomsRequest*, UCreateRoomResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostRoomsFullResponse, FPostRoomsFullResponse);
