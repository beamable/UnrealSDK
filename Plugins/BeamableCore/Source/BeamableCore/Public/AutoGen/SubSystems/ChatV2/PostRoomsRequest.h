
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/CreateRoomRequestBody.h"
#include "BeamableCore/Public/AutoGen/CreateRoomResponse.h"

#include "PostRoomsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostRoomsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCreateRoomRequestBody* Body;

	// Beam Base Request Declaration
	UPostRoomsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|ChatV2", DisplayName="Beam - Make PostRooms",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UPostRoomsRequest* Make(int64 _ObjectId, bool _bKeepSubscribed, FString _RoomName, TArray<int64> _Players, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRoomsSuccess, FBeamRequestContext, Context, UPostRoomsRequest*, Request, UCreateRoomResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRoomsError, FBeamRequestContext, Context, UPostRoomsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostRoomsComplete, FBeamRequestContext, Context, UPostRoomsRequest*, Request);

using FPostRoomsFullResponse = FBeamFullResponse<UPostRoomsRequest*, UCreateRoomResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostRoomsFullResponse, FPostRoomsFullResponse);
